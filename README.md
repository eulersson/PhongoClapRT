# Phongo Clap RT

![](https://github.com/eulersson/PhongoClapRT/raw/main/FinalSubmission/sample_images/colorful.png)

[Documentation](https://eulersson.github.io/PhongoClapRT/)

## Brief

Phongo Clap RT is an offline raytracing renderer developed from scratch in C++.
It supports fundamental rendering techniques and lighting models, aiming to
simulate realistic 3D scenes through physically inspired algorithms. This
version was submitted as part of an academic project, but I’m actively extending
it with more advanced features like path tracing and global illumination.

### Core Features

- ✅ Ray-sphere intersection  
- ✅ Ray-plane intersection  
- ✅ Lighting attenuation  
- ✅ Hard shadows via raytraced shadow rays  
- ✅ Mirror-like reflections  
- ✅ Basic refraction  
- ✅ Phong illumination model  
- ✅ Supersampling-based antialiasing  
- ✅ Custom scene file parsing

## Usage

Using the renderer is straightforward: run the compiled binary and provide the
path to a valid scene file as an argument.  Please refer to the next section for
details on the scene file syntax. The parser was implemented manually without
the aid of parsing libraries, so the format is functional but not overly
forgiving.

Run the compiled binary with the path to your `.phg` scene file to begin rendering:


```
./clap [path to scene text file]
```

I recommend building the binary from source to ensure compatibility with your system.  
To do this, you will need **qmake** and **git** installed.  

If you'd like to try **Phongo Clap RT** on your machine, run the following commands:  

```
git clone https://github.com/eulersson/PhongoClapRT
cd PhongoClapRT/FinalSubmission
qmake
make
./clap scene_file.txt
```

For convenience, a precompiled binary is also provided in the repository.

## Scene File Syntax

**Please read this section carefully.**  

Before diving in, I recommend reviewing the sample scene file included in the project.  

Scene files are structured into three main parts:  
- A **header**  
- The **lights interface**  
- The **objects interface**  

### Scene File Sample [scene_file.txt]

```
NAME "colorful" DIMENSIONS ["500" "500"]
CAMERA ["0", "1", "-2"] ["0", "0", "6"]
DEPTH "4" ANTI-ALIASING "4"

Lights
{
    +light1 [ 5 5 3 ] [ 0.347 0.89 0.78 ] [ 0.347 0.89 0.78 ] 2 2 1
    +light2 [ -5 5 4.2 ] [ 1 1 1 ] [ 1 1 1 ] 2 2 1
    +light3 [ 0.9 2 -1 ] [ 1 1 1 ] [ 1 1 1 ] 0.2 0.2 1

+}

Objects
{
    $Plane plane1 -1 [ 0 1 0 ] @checker [ 0 0 0 ] [ 1 1 1 ] @specularHardness 4

    $Plane plane2 -4.90 [ 0 1 -1 ] [ 1 1 0 ] /

    $Sphere sphere1 [ 0 0 2 ] 0.8 [ 1 0 1 ] @specularHardness 5

    $Sphere sphere2 [ -1 1.2 0.2 ] 0.5 [ 0.1 0.4 0.95 ] @reflective 70

    $Sphere sphere4 [ 1.1 0.5 2.0 ] 0.1 [ 0 1 0 ] @refractive 1.2 100

    $Sphere sphere5 [ 0.7 0.95 0.3 ] 0.15 [ 1 1 0 ] @specularHardness 100

    $Sphere sphere6 [ 1.1 0 4.0 ] 0.1 [ 0.2 1 0.14 ] @specularHardness 100

    $Sphere sphere7 [ -0.9 0.15 0.8 ] 0.3 [ 1 0 0 ] @refractive 1.2 100

    $Sphere sphere8 [ 0.5 0.3 0.2 ] 0.2 [ 0 0.8 1 ] @refractive 1.2 100

    $Sphere sphere9 [ 0.3 1.4 3.2 ] 0.53 [ 1 0.4 0.2 ] @reflective 60
$}
```

### Header

The **header** section defines key scene parameters such as the project name,
image dimensions, camera settings, depth, and antialiasing options.  

Each property follows one of these formats:  

- `VARIABLE "VALUE"`  
- `VARIABLE ["VALUE" "VALUE"]`  

To avoid parsing errors, please use the exact syntax as shown below. You can
copy and paste this template into your scene file and modify the values as
needed.

```
NAME "fileName" DIMENSIONS ["width" "height"]
CAMERA ["posX", "posY", "posZ"] ["aimX", "aimY", "aimZ"]
DEPTH "recursive_depth" ANTI-ALIASING "aa"
```
* *replace the lowercase words with values, leaving the quotes " "*

For the lights interface each light declaration and definition should be started
by `+`, and everything should be wrapped as `Lights { [all the lights] +}`
*(don't forget the `+` before the closing brace)*. The definition follows this
pattern:


```
+light_name [ posX posY posZ ] [ diffR diffG diffB ] [ specR specG specB ] diffInt specInt falloff
```

**Please note:** When specifying tuples, the first and last values **must be separated by commas**, not just spaces.  

For example, writing `[posX posY posZ]` or `[ posX posY posZ]` will cause parsing errors.  

Use commas to separate the values, like `[posX, posY, posZ]`.

- `light_name` is self-explanatory
- `posX`, `posY`, and `posZ` refer to the light's position.
- `diffR`, `diffG`, `diffB` *[0-1] value* refer to the diffuse colour.
- `specR`, `specG`, `specB` *[0-1] value* refer to the specular colour.
- `diffInt` the amount of diffuse contribution emmited by the light.
- `specInt` amount of specular the light emits.
- `falloff` decay amount.

A sample:

```
Lights
{
    +light1 [ 5 5 3 ] [ 0.347 0.89 0.78 ] [ 0.347 0.89 0.78 ] 2 2 1
    +light2 [ -5 5 4.2 ] [ 1 1 1 ] [ 1 1 1 ] 2 2 1
    +light3 [ 0.9 2 -1 ] [ 1 1 1 ] [ 1 1 1 ] 0.2 0.2 1
+}
```

The object interface is similar. Everything is between `Objects { [...] $}`
*(do not forget dollar sign before closing brace)*. You can declare either
planes or spheres.

### Planes

A plane can be of two types, a **checkerboard plane** or a regular plane. To
define a **regular plane** do it as follows:

```
$Plane plane_name dist [ nX nY nZ ] [ cR cG cB ]
```

**Please note:** The values in each tuple must be separated by a single space without extra spaces at the start or end.  

For example, writing `[nX nY nZ]` or `[ nX nY nZ]` will cause parsing errors.  

Make sure there are no leading or trailing spaces inside the brackets.

- `plane_name` is self explanatory.
- `dist` is the distance from the origin.
- `nX, nY, nZ` *(no need to normalize, it's done for you)* are the normal components of the plane.
- `cR`, `cG`, `cB` *[0-1] values* are the colour components of the plane.

For a **checkerboard** plane the definition is a bit different:

```
$Plane plane_name dist [ nX nY nZ ] @checker [ col1R col1G col1B ] [ col2R col2G col2B ]
```

Take a look at the **@checker** token. after the checker token the parser will
be expecting two tuples of colours, do it as above, **putting spaces even before
the first element of the tuple**.

You can set the plane to have certain **specular** hardness by the keyword
`@specularHardness [value]`. Find some examples above.

### Spheres

Spheres are pretty simple.

```
$Sphere sphere_name [ cX cY cZ ] rad [ colR colG colB ]
```

- `cX`, `cY`, `cZ` are the world space coordinates of the sphere centres.
- `rad` is the radius of the sphere.
- `colR`, `colG`, `colB` are the colour values of the sphere.

##### Reflection

You can set reflection options using the keyword `@reflective percentage` where
the percentage will determine how reflective the sphere is.

##### Refraction

Refraction settings are set `@refraction index_of_refraction transparency` where
transparency is in %.

##### Sphecular hardness

Also you can set specular hardness for the objects that are not reflective or
refractive. I did it that way because I did a trick to make the
transparent/reflective objects look glossy. So if you use specular hardness
**you cannot use reflection or refraction**.

You have to stick to this structure.

## TO DO

- BRDF
- Implement SpotLight
- Ambient Occlusion
- Load OBJs
- Fresnel
- Depth of Field
- Implement OpenSubDiv
- Implement OpenEXR (just for fun)
- Stochastic Sampling to break aliasing a bit more
- Improve AA on refractions and reflections
- Make it multi-threaded
- Implement more light decays
- Implement Triangle-Ray intersection
- Improve shadows
- Implement more shapes
- Make specular compatible with refraction/reflection

## Some Renders

<img src ="https://github.com/eulersson/PhongoClapRT/raw/main/FinalSubmission/sample_images/aa_00.png" width="500" height="500" align="center" />
<p>... rendering with anti-aliasing value of 1</p>

<img src ="https://github.com/eulersson/PhongoClapRT/raw/main/FinalSubmission/sample_images/aa_16.png" width="500" height="500" align="center" />
<p>... rendering with anti-aliasing value of 16</p>

<img src ="https://github.com/eulersson/PhongoClapRT/raw/main/FinalSubmission/sample_images/interstellar.png" width="500" height="500" align="center" />
<p>... this happens if I don't clamp the light contributions to [0-1]</p>

<img src ="https://github.com/eulersson/PhongoClapRT/raw/main/FinalSubmission/sample_images/pink.png" width="500" height="500" align="center" />
<p>... same here. Not clamping the values produces interesting results!</p>

<img src ="https://github.com/eulersson/PhongoClapRT/raw/main/FinalSubmission/sample_images/simple_phong.png" width="500" height="500" align="center" />
<p>... first tests when I implemented the Phong shader and tweaked it.</p>

<img src ="https://github.com/eulersson/PhongoClapRT/raw/main/FinalSubmission/sample_images/colorful.png" width="500" height="500" align="center" />
<p>... my favourite render. The scene_file I include renders this.</p>

## Bibliography

**Pharr, M.** and **Humphreys, G**., 2010. *Physically Based Rendering.* Burlington: Morgan Kaufmann Publishers Haines E.

**Glassner, A.**, 1989. *An Overview of Ray Tracing* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 1-31

**Haines, E.**, 1989. *Essential Ray Tracing Algorithms* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 33-77

**Hanrahan, P.**, 1989 *A Survey of Ray-Surface Intersection Algorithms* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 79-119

**Glassner, A.**, 1989 *Surface Physics for Ray Tracing* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 121-160

**Newman, W.** 1975 *Illumination for Computer Generated Pictures* [online] [checked 2015] [http://www.cs.northwestern.edu/~ago820/cs395/Papers/Phong_1975.pdf]

**Scratchapixel** (no date) *Introduction to Ray Tracing: a Simple Method for Creating 3D Images.* Scratchpixel [online] [checked 2015] Available from: http://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing

**Scratchapixel** (no date) *Introduction to Ray Tracing: a Simple Method for Creating 3D Images.* Scratchpixel [online] [checked 2015] Available from: http://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing

**Delphi3D** (no date) *Delphi3D [Archive]- Rapid OpenGL Development* Delphi3D [online] [checked 2015] Available from: http://www.gameprogrammer.net/delphi3dArchive/phongfordummies.htm

**Phong, B. T.**r, 1975. *Illumination for computer generated pictures* [online] [checked 2015] Utah: Communications of ACM, 18. Available from: http://www.cs.northwestern.edu/~ago820/cs395/Papers/Phong_1975.pdf

**cplusplus.com** (no date) *Input/output with files - C++ Tutorials* cplusplus.com [online] [checked 2015] Available from: http://www.cplusplus.com/doc/tutorial/files/

**Boris Schäling** (2008-2015) *Chapter 10. Boost.Tokenizer* The Boost C++ Libraries [online] [checked 2015] Available from: http://theboostcpplibraries.com/boost.tokenizer

**Siek, J.** and **Bandela J. R.** (2000-2001) *Boost Tokenizer Overview - 1.58.0* Boost C++ Libraries [online] [checked 2015] Available from: http://www.boost.org/doc/libs/1_58_0/libs/tokenizer/
