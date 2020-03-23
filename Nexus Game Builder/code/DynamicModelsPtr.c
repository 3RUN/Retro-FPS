#include <acknex.h>
#include <windows.h>
#include <d3d9.h>

/************************************************************************************************/
/*	DX9 API Includes                                                                             */
/************************************************************************************************/
typedef struct _D3DXWELDEPSILONS {
  FLOAT Position;
  FLOAT BlendWeights;
  FLOAT Normal;
  FLOAT PSize;
  FLOAT Specular;
  FLOAT Diffuse;
  FLOAT Texcoord[8];
  FLOAT Tangent;
  FLOAT Binormal;
  FLOAT TessFactor;
} D3DXWELDEPSILONS;

#define D3DXWELDEPSILONS_WELDALL             1
#define D3DXWELDEPSILONS_WELDPARTIALMATCHES  2
#define D3DXWELDEPSILONS_DONOTREMOVEVERTICES 4
#define D3DXWELDEPSILONS_DONOTSPLIT          8 

HRESULT WeldVertices(
	LPD3DXMESH pMesh,
	DWORD Flags,
	D3DXWELDEPSILONS *pEpsilons,
	DWORD *pAdjacencyIn,
	DWORD *pAdjacencyOut,
	DWORD *pFaceRemap,
	LPD3DXBUFFER *ppVertexRemap);

typedef void D3DXEFFECTINSTANCE;

HRESULT SaveMeshToX(
	char *pFilename,
	LPD3DXMESH pMesh,
	DWORD *pAdjacency,
	D3DXMATERIAL *pMaterials,
	D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	DWORD Format);

DynamicModel* dmdl_create ()
{
	return dmdl_create ( DMDL_MAX_VERTEXCOUNT, DMDL_MAX_INDEXCOUNT );
}

DynamicModel* dmdl_create ( int vertexCount, int faceCount )
{
	DynamicModel *model = sys_malloc(sizeof(DynamicModel));
	model->vertexBuffer = sys_malloc(sizeof(D3DVERTEX)*vertexCount);
	model->attributeBuffer = sys_malloc(sizeof(DWORD)*faceCount);
	model->indexBuffer = sys_malloc(sizeof(short)*faceCount*3);
	model->vertexCount = 0;
	model->vertexMax = vertexCount;
	model->faceCount = 0;
	model->faceMax = faceCount;
	model->skin[0] = NULL;
	model->skin[1] = NULL;
	model->skin[2] = NULL;
	model->skin[3] = NULL;
	
	return model;
}

void dmdl_save_buffers ( DynamicModel *model, char *filename )
{
	int headerSize = 2 * sizeof(int);
	int vBufferSize = model->vertexCount * sizeof(D3DVERTEX);
	int aBufferSize = model->faceCount * sizeof(DWORD);
	int iBufferSize = model->faceCount * 3 * sizeof(short);
	int totalSize = headerSize + vBufferSize + aBufferSize + iBufferSize;
	BYTE *buffer = sys_malloc ( totalSize );
	BYTE *bufferTemp = buffer;
	memcpy ( bufferTemp, &model->vertexCount, sizeof(int) );
	bufferTemp += sizeof(int); 
	memcpy ( bufferTemp, &model->faceCount, sizeof(int) );
	bufferTemp += sizeof(int);
	memcpy ( bufferTemp, model->vertexBuffer, vBufferSize );
	bufferTemp += vBufferSize;
	memcpy ( bufferTemp, model->attributeBuffer, aBufferSize );
	bufferTemp += aBufferSize;
	memcpy ( bufferTemp, model->indexBuffer, iBufferSize );
	file_save ( filename, buffer, totalSize );
	sys_free ( buffer );
}

DynamicModel *dmdl_create_fixed_from_file ( char *filename )
{
	if ( !file_exists(filename) ) return;
	long size;
	void *filebuffer = file_load ( filename, NULL, &size );
	BYTE *buffer = (void*)filebuffer;
	int vertexCount;
	int size_of_int = sizeof(int);
	memcpy ( &vertexCount, buffer, size_of_int );
	buffer += size_of_int;
	int faceCount;
	memcpy ( &faceCount, buffer, size_of_int );
	buffer += size_of_int;
	
	int headerSize = 2 * size_of_int;
	int vBufferSize = vertexCount * sizeof(D3DVERTEX);
	int aBufferSize = faceCount * sizeof(DWORD);
	int iBufferSize = faceCount * 3 * sizeof(short);
	
	D3DVERTEX *vBuffer = buffer;
	buffer += vBufferSize;
	
	DWORD *aBuffer = buffer;
	buffer += aBufferSize;
	
	short *iBuffer = buffer;
	
	DynamicModel *model = dmdl_create ( vertexCount, faceCount );
	memcpy ( model->vertexBuffer, vBuffer, vBufferSize );
	memcpy ( model->attributeBuffer, aBuffer, aBufferSize );
	memcpy ( model->indexBuffer, iBuffer, iBufferSize );
	
	model->vertexCount = vertexCount;
	model->faceCount = faceCount;
	
	long size;
	file_load ( NULL, filebuffer, &size );
	
	return model;
}

void dmdl_delete(DynamicModel *model)
{
	sys_free(model->vertexBuffer);
	sys_free(model->attributeBuffer);
	sys_free(model->indexBuffer);
	sys_free(model);
}

LPD3DXMESH dmdl_create_mesh(DynamicModel *model)
{
	if(model == NULL) return 0;

	LPD3DXMESH mesh;
	
	if(model->vertexCount <= 0)
	{
		return NULL;
	}
	if(model->faceCount <= 0)
	{
		return NULL;
	}

	D3DVERTEX *vertexBuffer;
	short *indexBuffer;
	DWORD *attributeBufferResult;
	
	D3DXCreateMesh(model->faceCount,model->vertexCount,D3DXMESH_MANAGED,pvertexdecl,pd3ddev,&mesh);
	mesh->LockVertexBuffer(0, &vertexBuffer);
	mesh->LockIndexBuffer(0, &indexBuffer);
	mesh->LockAttributeBuffer(0, &attributeBufferResult);
	
	memcpy(vertexBuffer,model->vertexBuffer,model->vertexCount * sizeof(D3DVERTEX));
	memcpy(indexBuffer,model->indexBuffer,3 * model->faceCount * sizeof(short));
	//memcpy(attributeBufferResult,model->attributeBuffer,model->vertexCount * sizeof(DWORD));
	
	mesh->UnlockVertexBuffer();
	mesh->UnlockIndexBuffer();
	mesh->UnlockAttributeBuffer();
	
	void *_nullPtr = NULL;
	
	if((DMDLSettings.flags & DMDL_OPTIMIZE) != 0)
	{
		D3DXWELDEPSILONS Epsilons;
		// Set epsilon values
		Epsilons.Normal = 0.001;
		Epsilons.Position = 0.1; 
		WeldVertices(	&mesh,
						D3DXWELDEPSILONS_WELDPARTIALMATCHES,
						&Epsilons,
						_nullPtr,
						_nullPtr,
						_nullPtr,
						_nullPtr);
	}
	
	if((DMDLSettings.flags & DMDL_FIXNORMALS) != 0)
	{
		D3DXComputeNormals((LPD3DXBASEMESH)mesh, _nullPtr);
	}
	
	return mesh;
}

ENTITY* dmdl_create_instance(DynamicModel *model, VECTOR *pos, EVENT act)
{
	if(model == NULL) return NULL;
	
	ENTITY* ent = ent_create(CUBE_MDL,pos,NULL);
	ent_clone(ent);
	
	LPD3DXMESH mesh = dmdl_create_mesh(model);
	if(mesh == NULL) return NULL;
	
	ent_setmesh(ent,mesh,0,0);
	
	int i;
	for(i = 0; i < 4; i++)
	{
		BMAP* skinSource = model->skin[i];
		if(skinSource)
		{
			if(DMDLSettings.flags & DMDL_CLONE_TEX)
			{
				var format = bmap_lock(skinSource, 0); bmap_unlock(skinSource);
				BMAP* skinTarget = bmap_createblack(bmap_width(skinSource),bmap_height(skinSource),format);
				bmap_blit(skinTarget,skinSource,NULL,NULL);
				ent_setskin(ent,skinTarget,i + 1);
			}
			else
			{
				ent_setskin(ent,skinSource,i + 1);
			}
		}
	}
	
	if(act != NULL)
	{
		me = ent;
		action dmdl_temporary_action();
		dmdl_temporary_action = act;
		dmdl_temporary_action();
		me = NULL;
	}
	
	
	return ent;
}

void dmdl_add_face(DynamicModel *model, DYNAMIC_FACE *face)
{
	if(model == NULL) return;
	if(face == NULL) return;
	
	int iVertexStartOffset = model->vertexCount;
	int iFaceStartOffset = model->faceCount;
	int i;
	// Copy vertices
	for(i = 0; i < 3; i++)
	{
		D3DVERTEX* vSource = &(face->v[i]);
		D3DVERTEX* vTarget = model->vertexBuffer + iVertexStartOffset + i;
		memcpy(vTarget,vSource,sizeof(D3DVERTEX));
		*( model->indexBuffer + i + 3 * iFaceStartOffset ) = iVertexStartOffset + i;
	}
	
	model->vertexCount += 3;
	model->faceCount += 1;
}

void dmdl_add_quad(DynamicModel *model, DYNAMIC_QUAD *quad)
{
	if(model == NULL) return;
	if(quad == NULL) return;
	
	short vertices[4];
	int iVertexStartOffset = model->vertexCount;
	int iFaceStartOffset = model->faceCount;
	int i;
	
	// Copy vertices
	for(i = 0; i < 4; i++)
	{
		D3DVERTEX* vSource = &(quad->v[i]);
		D3DVERTEX* vTarget = model->vertexBuffer + iVertexStartOffset + i;
		memcpy(vTarget,vSource,sizeof(D3DVERTEX));
		
		vertices[i] = iVertexStartOffset + i;
	}
	
	// Face 1
	*( model->indexBuffer + 0 + 3 * iFaceStartOffset ) = vertices[2];
	*( model->indexBuffer + 1 + 3 * iFaceStartOffset ) = vertices[1];
	*( model->indexBuffer + 2 + 3 * iFaceStartOffset ) = vertices[0];
	
	// Face 2
	*( model->indexBuffer + 3 + 3 * iFaceStartOffset ) = vertices[1];
	*( model->indexBuffer + 4 + 3 * iFaceStartOffset ) = vertices[2];
	*( model->indexBuffer + 5 + 3 * iFaceStartOffset ) = vertices[3];
	
	// Index count per dynamic face
	model->vertexCount += 4;
	model->faceCount += 2;
}

void dmdl_add_entity(DynamicModel *model, ENTITY *ent)
{
	dmdl_add_mesh(model, ent_getmesh(ent, 0 ,0), &(ent->x), &(ent->pan), &(ent->scale_x));
}

void dmdl_add_mesh(DynamicModel *model, LPD3DXMESH mesh)
{
	dmdl_add_mesh(model, mesh, nullvector, nullvector, vector(1,1,1));
}

void dmdl_add_mesh(DynamicModel *model, LPD3DXMESH mesh, VECTOR *offset)
{
	dmdl_add_mesh(model, mesh, offset, nullvector, vector(1,1,1));
}

void dmdl_add_mesh(DynamicModel *model, LPD3DXMESH mesh, VECTOR *offset, ANGLE *rotation)
{
	dmdl_add_mesh(model, mesh, offset, rotation, vector(1,1,1));
}

void dmdl_add_mesh(DynamicModel *model, LPD3DXMESH mesh, VECTOR *offset, ANGLE *rotation, VECTOR *scale)
{
	if(model == NULL) return;
	if(mesh == NULL) return;
	sys_marker("000");
	D3DVERTEX *vertexBufferMesh;
	short *indexBufferMesh;
	DWORD *attributeBuffer;
	sys_marker("001");
	
	int meshVertexCount = mesh->GetNumVertices();
	int meshFaceCount = mesh->GetNumFaces();
	
	sys_marker("002");
	if(model->vertexCount + meshVertexCount > model->vertexMax)
		return;
	
	sys_marker("003");
	if(model->faceCount + meshFaceCount > model->faceMax )
		return;
	
	sys_marker("004");
	mesh->LockVertexBuffer(0, &vertexBufferMesh);
	mesh->LockIndexBuffer(0, &indexBufferMesh);
	mesh->LockAttributeBuffer(0, &attributeBuffer);
	
	sys_marker("005");
	int i;
	for(i = 0; i < meshVertexCount; i++)
	{
		sys_marker("010");
		memcpy( model->vertexBuffer+model->vertexCount+i,vertexBufferMesh,sizeof(D3DVERTEX));
		
		sys_marker("011");
		VECTOR pos;
		pos.x = (model->vertexBuffer+model->vertexCount+i)->x;
		pos.z = (model->vertexBuffer+model->vertexCount+i)->y;
		pos.y = (model->vertexBuffer+model->vertexCount+i)->z;
		
		sys_marker("012");
		vec_mul(&pos, scale);
		vec_rotate(&pos, rotation);
		vec_add(&pos, offset);
		
		sys_marker("013");
		(model->vertexBuffer+model->vertexCount+i)->x = pos.x;
		(model->vertexBuffer+model->vertexCount+i)->z = pos.y;
		(model->vertexBuffer+model->vertexCount+i)->y = pos.z;
		
		sys_marker("014");
		normal.x = (model->vertexBuffer+model->vertexCount+i)->nx;
		normal.z = (model->vertexBuffer+model->vertexCount+i)->ny;
		normal.y = (model->vertexBuffer+model->vertexCount+i)->nz;
		
		sys_marker("015");
		vec_rotate(&normal, rotation);
		
		sys_marker("016");
		(model->vertexBuffer+model->vertexCount+i)->nx = normal.x;
		(model->vertexBuffer+model->vertexCount+i)->nz = normal.y;
		(model->vertexBuffer+model->vertexCount+i)->ny = normal.z;
		
		
		sys_marker("017");
		vertexBufferMesh++;
	}
	
	sys_marker("006");
	for ( i=0; i<meshFaceCount; i+=1 )
	{
		*(model->attributeBuffer+model->faceCount+i) = *attributeBuffer;
		attributeBuffer++;
		
	}
	sys_marker("007");
	for(i = 0; i < meshFaceCount * 3; i++)
	{
		*(model->indexBuffer + i + model->faceCount * 3) = model->vertexCount + *indexBufferMesh;
		indexBufferMesh++;
	}
	
	sys_marker("008");
	mesh->UnlockVertexBuffer();
	mesh->UnlockIndexBuffer();
	mesh->UnlockAttributeBuffer();
	
	sys_marker("009");
	model->vertexCount += meshVertexCount;
	model->faceCount += meshFaceCount;
}

void dmdl_merge ( DynamicModel *model, DynamicModel *mesh )
{
	dmdl_merge ( model, mesh, nullvector, nullvector, vector(1,1,1) );
}

void dmdl_merge ( DynamicModel *model, DynamicModel *mesh, VECTOR *offset )
{
	dmdl_merge ( model, mesh, offset, nullvector, vector(1,1,1) );
}

void dmdl_merge ( DynamicModel *model, DynamicModel *mesh, VECTOR *offset, ANGLE *rotation )
{
	dmdl_merge ( model, mesh, offset, rotation, vector(1,1,1) );
}

void dmdl_merge ( DynamicModel *model, DynamicModel *mesh, VECTOR *offset, ANGLE *rotation, VECTOR *scale )
{
	if(model == NULL) return;
	if(mesh == NULL) return;
	
	if(model->vertexCount + mesh->vertexCount > model->vertexMax)
		return;
	
	if(model->faceCount + mesh->faceCount > model->faceMax )
		return;
		
	int i;
	for(i = 0; i < mesh->vertexCount; i++)
	{
		memcpy ( model->vertexBuffer+model->vertexCount+i, mesh->vertexBuffer+i, sizeof(D3DVERTEX) );
		
		VECTOR pos;
		pos.x = (model->vertexBuffer+model->vertexCount+i)->x;
		pos.z = (model->vertexBuffer+model->vertexCount+i)->y;
		pos.y = (model->vertexBuffer+model->vertexCount+i)->z;
		
		vec_mul(&pos, scale);
		vec_rotate(&pos, rotation);
		vec_add(&pos, offset);
		
		(model->vertexBuffer+model->vertexCount+i)->x = pos.x;
		(model->vertexBuffer+model->vertexCount+i)->z = pos.y;
		(model->vertexBuffer+model->vertexCount+i)->y = pos.z;
		
		normal.x = (model->vertexBuffer+model->vertexCount+i)->nx;
		normal.z = (model->vertexBuffer+model->vertexCount+i)->ny;
		normal.y = (model->vertexBuffer+model->vertexCount+i)->nz;
		
		vec_rotate(&normal, rotation);
		
		(model->vertexBuffer+model->vertexCount+i)->nx = normal.x;
		(model->vertexBuffer+model->vertexCount+i)->nz = normal.y;
		(model->vertexBuffer+model->vertexCount+i)->ny = normal.z;
		
	}
	
	for ( i=0; i<mesh->faceCount; i+=1 )
	{
		*(model->attributeBuffer + model->faceCount + i) = *(mesh->attributeBuffer + i);
	}
	for(i = 0; i < mesh->faceCount * 3; i++)
	{
		*( model->indexBuffer + i + model->faceCount * 3 ) = model->vertexCount + *(mesh->indexBuffer+i);
	}
	
	model->vertexCount += mesh->vertexCount;
	model->faceCount += mesh->faceCount;
}

void dmdl_merge_uv2 ( DynamicModel *model, DynamicModel *mesh, VECTOR *offset, ANGLE *rotation, VECTOR *scale, VECTOR *uvOffset, double uvScale)
{
	if(model == NULL) return;
	if(mesh == NULL) return;
	
	if(model->vertexCount + mesh->vertexCount > model->vertexMax)
		return;
	
	if(model->faceCount + mesh->faceCount > model->faceMax )
		return;
		
	int i;
	for(i = 0; i < mesh->vertexCount; i++)
	{
		D3DVERTEX *_v = model->vertexBuffer + model->vertexCount + i;
		
		memcpy ( _v, mesh->vertexBuffer+i, sizeof(D3DVERTEX) );
		
		VECTOR pos;
		pos.x = _v->x;
		pos.z = _v->y;
		pos.y = _v->z;
		
		vec_mul(&pos, scale);
		vec_rotate(&pos, rotation);
		vec_add(&pos, offset);
		
		_v->x = pos.x;
		_v->z = pos.y;
		_v->y = pos.z;
		
		normal.x = _v->nx;
		normal.z = _v->ny;
		normal.y = _v->nz;
		
		vec_rotate(&normal, rotation);
		
		_v->nx = normal.x;
		_v->nz = normal.y;
		_v->ny = normal.z;
		
		_v->u2 += uvOffset->x;
		_v->v2 += uvOffset->y;
		
		_v->u2 *= uvScale;
		_v->v2 *= uvScale;
	}
	
	for ( i=0; i<mesh->faceCount; i+=1 )
	{
		*(model->attributeBuffer + model->faceCount + i) = *(mesh->attributeBuffer + i);
	}
	for(i = 0; i < mesh->faceCount * 3; i++)
	{
		*( model->indexBuffer + i + model->faceCount * 3 ) = model->vertexCount + *(mesh->indexBuffer+i);
	}
	
	model->vertexCount += mesh->vertexCount;
	model->faceCount += mesh->faceCount;
}

//void dmdl_save(DynamicModel *model, char *filename)
//{
//	LPD3DXMESH mesh = dmdl_create_mesh(model);
//	
//	D3DMATERIAL9 mat9_1;
//	/*mat9_1.Diffuse.r = 255;
//	mat9_1.Ambient.r = 255;
//	mat9_1.Specular.r = 255;
//	mat9_1.Emissive.r = 255;
//	mat9_1.Power = 1.0;*/
//	
//	
//	D3DXMATERIAL mat1;
//	memcpy(&mat1.MatD3D, &mat9_1, sizeof(D3DMATERIAL9));
//	
//	char buffer[256];
//	strcpy(buffer, "test.bmp");
//	mat1.pTextureFilename = buffer;
//	
//	SaveMeshToX(
//		filename,
//		mesh,
//		NULL,
//		&mat1,
//		NULL,
//		1,
//		DMDLSettings.xFormat);
//	
//	/*SaveMeshToX(
//		filename,
//		mesh,
//		NULL,
//		NULL,
//		NULL,
//		0,
//		DMDLSettings.xFormat);*/
//}

int dmdl_add_vertex(DynamicModel *_model, D3DVERTEX *_v)
{
	int index = _model->vertexCount;
	memcpy(_model->vertexBuffer+index, _v, sizeof(D3DVERTEX));
	_model->vertexCount +=1;
	return index;
}

void dmdl_connect_vertices(DynamicModel *_model, int _v1, int _v2, int _v3)
{
	int bufferIndex = 3 * _model->faceCount;
	*(_model->indexBuffer+bufferIndex + 0) = _v1;
	*(_model->indexBuffer+bufferIndex + 1) = _v2;
	*(_model->indexBuffer+bufferIndex + 2) = _v3;
	_model->faceCount +=1;
}

void dmdl_empty ( DynamicModel *_model ) 
{
	if(_model == NULL) return;
	_model->vertexCount = 0;
	_model->faceCount = 0;
	(_model->skin)[0] = NULL;
	(_model->skin)[1] = NULL;
	(_model->skin)[2] = NULL;
	(_model->skin)[3] = NULL;
}

void dmdl_set_tangent(DynamicModel *_model, double _x3, double _y3, double _z3, double _w3) {
	D3DVERTEX *_v = _model->vertexBuffer;
	D3DVERTEX *_vLast = _v + _model->vertexCount;
	for (; _v<_vLast; _v+=1) {
		_v->x3 = _x3;
		_v->y3 = _y3;
		_v->z3 = _z3;
		_v->w3 = _w3;
	}
}









