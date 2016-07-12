#ifndef HSCORE_LINMATH_H
#define HSCORE_LINMATH_H

#pragma once

/*
* Copyright (c) 2015-2016 The Khronos Group Inc.
* Copyright (c) 2015-2016 Valve Corporation
* Copyright (c) 2015-2016 LunarG, Inc.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and/or associated documentation files (the "Materials"), to
* deal in the Materials without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Materials, and to permit persons to whom the Materials are
* furnished to do so, subject to the following conditions:
*
* The above copyright notice(s) and this permission notice shall be included in
* all copies or substantial portions of the Materials.
*
* THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE
* USE OR OTHER DEALINGS IN THE MATERIALS.
*
* Relicensed from the WTFPL (http://www.wtfpl.net/faq/).
*/

#include <math.h>

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

typedef float vec3raw[3];

static inline void vec3_add(vec3raw r, vec3raw const a, vec3raw const b);
static inline void vec3_sub(vec3raw r, vec3raw const a, vec3raw const b);
static inline void vec3_scale(vec3raw r, vec3raw const v, float const s);
static inline float vec3_mul_inner(vec3raw const a, vec3raw const b);
static inline void vec3_mul_cross(vec3raw r, vec3raw const a, vec3raw const b);
static inline float vec3_len(vec3raw const v);
static inline void vec3_norm(vec3raw r, vec3raw const v);
static inline void vec3_reflect(vec3raw r, vec3raw const v, vec3raw const n);

typedef float vec4raw[4];
static inline void vec4_add(vec4raw r, vec4raw const a, vec4raw const b);
static inline void vec4_sub(vec4raw r, vec4raw const a, vec4raw const b);
static inline void vec4_scale(vec4raw r, vec4raw v, float s);
static inline float vec4_mul_inner(vec4raw a, vec4raw b);
static inline void vec4_mul_cross(vec4raw r, vec4raw a, vec4raw b);
static inline float vec4_len(vec4raw v);
static inline void vec4_norm(vec4raw r, vec4raw v);
static inline void vec4_reflect(vec4raw r, vec4raw v, vec4raw n);
typedef vec4raw mat4x4raw[4];
static inline void mat4x4_identity(mat4x4raw M);
static inline void mat4x4_dup(mat4x4raw M, mat4x4raw N);
static inline void mat4x4_row(vec4raw r, mat4x4raw M, int i);
static inline void mat4x4_col(vec4raw r, mat4x4raw M, int i);
static inline void mat4x4_transpose(mat4x4raw M, mat4x4raw N);
static inline void mat4x4_add(mat4x4raw M, mat4x4raw a, mat4x4raw b);
static inline void mat4x4_sub(mat4x4raw M, mat4x4raw a, mat4x4raw b);
static inline void mat4x4_scale(mat4x4raw M, mat4x4raw a, float k);
static inline void mat4x4_scale_aniso(mat4x4raw M, mat4x4raw a, float x, float y,
	float z);
static inline void mat4x4_mul(mat4x4raw M, mat4x4raw a, mat4x4raw b);
static inline void mat4x4_mul_vec4(vec4raw r, mat4x4raw M, vec4raw v);
static inline void mat4x4_translate(mat4x4raw T, float x, float y, float z);
static inline void mat4x4_translate_in_place(mat4x4raw M, float x, float y,
	float z);
static inline void mat4x4_from_vec3_mul_outer(mat4x4raw M, vec3raw a, vec3raw b);
static inline void mat4x4_rotate(mat4x4raw R, mat4x4raw M, float x, float y, float z,
	float angle);
static inline void mat4x4_rotate_X(mat4x4raw Q, mat4x4raw M, float angle);
static inline void mat4x4_rotate_Y(mat4x4raw Q, mat4x4raw M, float angle);
static inline void mat4x4_rotate_Z(mat4x4raw Q, mat4x4raw M, float angle);
static inline void mat4x4_invert(mat4x4raw T, mat4x4raw M);
static inline void mat4x4_orthonormalize(mat4x4raw R, mat4x4raw M);
static inline void mat4x4_frustum(mat4x4raw M, float l, float r, float b, float t,
	float n, float f);
static inline void mat4x4_ortho(mat4x4raw M, float l, float r, float b, float t,
	float n, float f);
static inline void mat4x4_perspective(mat4x4raw m, float y_fov, float aspect,
	float n, float f);
static inline void mat4x4_look_at(mat4x4raw m, vec3raw eye, vec3raw center, vec3raw up);

typedef float quatraw[4];
static inline void quat_identity(quatraw q);
static inline void quat_add(quatraw r, quatraw a, quatraw b);
static inline void quat_sub(quatraw r, quatraw a, quatraw b);
static inline void quat_mul(quatraw r, quatraw p, quatraw q);
static inline void quat_scale(quatraw r, quatraw v, float s);
static inline float quat_inner_product(quatraw a, quatraw b);
static inline void quat_conj(quatraw r, quatraw q);
#define quat_norm vec4_norm
static inline void quat_mul_vec3(vec3raw r, quatraw q, vec3raw v);
static inline void mat4x4_from_quat(mat4x4raw M, quatraw q);
static inline void mat4x4o_mul_quat(mat4x4raw R, mat4x4raw M, quatraw q);
static inline void quat_from_mat4x4(quatraw q, mat4x4raw M);

struct vec3
{
	vec3(float_t x, float_t y, float_t z) { d[0] = x, d[1] = y, d[2] = z; };
	vec3raw d;
};
struct vec4
{
	vec4(float_t x, float_t y, float_t z, float_t w) { d[0] = x, d[1] = y, d[2] = z, d[3] = w; };
	vec4raw d;
};

#include "linmath.inl"

#endif