technique z_write
{
	pass p0
	{
		ZWriteEnable = True;
		AlphaBlendEnable = True;
		AlphaTestEnable = True;
	}
}

technique fallback
{
	pass p0 {}
}