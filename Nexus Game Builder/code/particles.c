
// randomize given vector within the given range
void vec_randomize(var *vec, var range)
{
    vec[0] = random(1) - 0.5;
    vec[1] = random(1) - 0.5;
    vec[2] = random(1) - 0.5;
    vec_normalize(vec, random(range));
}

// slow down given particle
void particle_slow_down(PARTICLE *p, var value)
{
    VECTOR temp_pos;
    vec_set(&temp_pos, &p->vel_x);
    vec_normalize(&temp_pos, minv(vec_length(&temp_pos), value * time_step));
    vec_inverse(&temp_pos);
    vec_add(&p->vel_x, &temp_pos);
}

// hide particles in fog
void particle_hide_in_fog(PARTICLE *p)
{
    // trick to hide particles in the fog
    if (vec_dist(&camera->x, &p->x) > camera->fog_end)
    {
        p->red -= (p->red - 0) * time_step;
        p->green -= (p->green - 0) * time_step;
        p->blue -= (p->blue - 0) * time_step;
    }
}

// smoke trail fading event function
void smoketrail_fade_function(PARTICLE *p)
{
    particle_slow_down(p, 0.9);
    particle_hide_in_fog(p);

    // fade smoke's color to make it darker
    p->blue -= (p->blue - p->skill_x) * 0.75 * time_step;
    p->red -= (p->red - p->skill_x) * 0.75 * time_step;
    p->green -= (p->green - p->skill_x) * 0.75 * time_step;
}

// simple smoketrail particles
void smoketrail_particle(PARTICLE *p)
{
    vec_set(&p->vel_x, vector(random(4) - 2, random(4) - 2, random(4) - 2));
    p->bmap = smoke_png;
    vec_set(&p->blue, vector(random(32), 64 + random(64), 128 + random(128)));
    p->skill_x = random(32); // color to fade at

    p->size = 6 + random(1);
    p->lifespan = 3 + random(1);
    p->alpha = 100;
    p->flags |= (MOVE | TRANSLUCENT | NOFILTER);
    p->event = smoketrail_fade_function;
}