#ifndef _PARTICLES_H_
#define _PARTICLES_H_

// This header handles everything related to particles

// randomize given vector within the given range
void vec_randomize(var *vec, var range);

// slow down given particle
void particle_slow_down(PARTICLE *p, var value);

// hide particles in fog
void particle_hide_in_fog(PARTICLE *p);

// smoke trail fading event function
void smoketrail_fade_function(PARTICLE *p);

// simple smoketrail particles
void smoketrail_particle(PARTICLE *p);

#endif