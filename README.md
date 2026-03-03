# hx-math
Vector, Matrix, and Math library for 4D, 3D, and 2D Computer Graphics

Tested in MSVC and GCC (Ubuntu)

## Data types
### Vector
- vec5f, vec5i
- vec4f, vec4i, vec4u
- vec3f, vec3u
- vec2f, vec2i, vec2u

### Matrix
- mat5
- mat4
- mat3

### Axis-Aligned Bounding Box
- aabb4f
- aabb4i
- aabb3f

### Rotors
- rotor4

### Orthonormal Basis
- ONB3 based on "Building an Orthonormal Basis, Revised" by Duff, Burgess, Christensen, Hery, Kensler, Liani, and Villemin
- ONB4 using optimized rotor4 rotation

## Usage:
```
TODO: usage examples
hxm::vec4f();
hxm::mat5();
hxm::ray4();
hxm::aabb4f();
hxm::rotor4();
hxm::euler6();
hxm::toRad();
etc.
```

### TODO:
- Standardize vec, mat, and aabb APIs
- ~~Add some Rotor rotation code~~
- ~~Unit tests and/or sample project~~
- ~~ONB (Orthonormal Basis)~~
- Spherical-to-Cartesian and Cartesian-to-Spherical conversion
- Header-only
- Version number
- Double-precision
