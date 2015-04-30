#Phongo Clap RT

![](https://github.com/docwhite/docwhite-CA1/raw/master/FinalSubmission/sample_images/colorful.png)

##Brief
My project consists on a raytracing offline renderer. This is what I handed in but I will be extending it to features
like path tracing. A full list about the further things I would like to do are listed after the usage section. My
raytracer features:

* Sphere-Ray Intersections
* Plane-Ray Intersections
* Lighting decay
* Reflection
* Refraction
* Phong Shading Model
* Antialiasing
* File parsing

##Usage
Its usage is fairly simple. You just have to run the binary followed by the path where the scene file is located. Read
carefully how the syntax works on the next section because it is not particulary straight-forward due to my lack of
knowledge with parsing frameworks.
```
./clap [path to scene text file]
```

##Scene File Syntax
**Please read this section carefully.** I would first suggest you to take a look at a sample image file that I included
with the project. Scene files consist on three parts: a header, the lights interface and the objects interface.

### Header
The header part contains the information about what the name of the project is, the dimensions, camera, depth and
antialiasing.
```
NAME "example" DIMENSIONS ["200" "200"]
CAMERA ["0", "1", "-2"] ["0", "0", "6"]
DEPTH "4" ANTI-ALIASING "2"
```


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

    $Sphere sphere2 [ -1 1.2 0.2 ] 0.5 [ 0.1 0.4 0.95 ] @reflective 70;

    $Sphere sphere4 [ 1.1 0.5 2.0 ] 0.1 [ 0 1 0 ] @refractive 1.2 100

    $Sphere sphere5 [ 0.7 0.95 0.3 ] 0.15 [ 1 1 0 ] @specularHardness 100

    $Sphere sphere6 [ 1.1 0 4.0 ] 0.1 [ 0.2 1 0.14 ] @specularHardness 100

    $Sphere sphere7 [ -0.9 0.15 0.8 ] 0.3 [ 1 0 0 ] @refractive 1.2 100

    $Sphere sphere8 [ 0.5 0.3 0.2 ] 0.2 [ 0 0.8 1 ] @refractive 1.2 100

    $Sphere sphere9 [ 0.3 1.4 3.2 ] 0.53 [ 1 0.4 0.2 ] @reflective 60;
$}

```

You have to stick to this structure.

##Documentation
http://ramonblanquer.com/doc/phongo/index.html

##TO DO
- (after deadline) Ambient Occlusion
- (after deadline) Fresnel
- (after deadline) BRDF
- (after deadline) Depth of Field
- (after deadline) Implement OpenSubDiv
- (after deadline) Implement OpenEXR
- (after deadline) Stochastic Sampling to break aliasing
- (after deadline) Improve AA on refractions and reflections
- (after deadline) Make it multi-threaded


Yet to be written. Docs.

##Bibliography
**Pharr, M.** and **Humphreys, G**., 2010. *Physically Based Rendering.* Burlington: Morgan Kaufmann Publishers Haines E.

**Glassner, A.**, 1989. *An Overview of Ray Tracing* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 1-31

**Haines, E.**, 1989. *Essential Ray Tracing Algorithms* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 33-77

**Hanrahan, P.**, 1989 *A Survey of Ray-Surface Intersection Algorithms* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 79-119

**Glassner, A.**, 1989 *Surface Physics for Ray Tracing* In: **Glassner, A.**, ed. *An Introduction To Ray Tracing* California: Academic Press, 121-160

**Newman, W.** 1975 *Illumination for Computer Generated Pictures* [online] Checked April 21st [http://www.cs.northwestern.edu/~ago820/cs395/Papers/Phong_1975.pdf]

http://en.wikipedia.org/wiki/Phong_reflection_model

http://www.scratchapixel.com/old/lessons/3d-basic-lessons/lesson-1-writing-a-simple-raytracer/

http://www.scratchapixel.com/old/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/ray-triangle-intersection-geometric-solution/

http://www.cplusplus.com/doc/tutorial/files/

http://www.gameprogrammer.net/delphi3dArchive/phongfordummies.htm

http://theboostcpplibraries.com/boost.tokenizer

http://www.boost.org/doc/libs/1_58_0/libs/tokenizer/


backup__________________________________________

NAME "example" DIMENSIONS ["500" "500"]
CAMERA ["0", "1", "-2"] ["0", "0", "6"]
DEPTH "4" ANTI-ALIASING "2"

Lights
{
    +light1 [ 1 5 2 ] [ 0.347 0.89 0.78 ] [ 0.347 0.89 0.78 ] 1 1 1
    +light2 [ -1 0.4 0 ] [ 1 1 1 ] [ 1 1 1 ] 0.5 0.5 1
    +light3 [ -1.5 1 10 ] [ 1 0 0 ] [ 1 0 0 ] 1 1 1
    +light4 [ 0.1 1.4 1 ] [ 1 1 1 ] [ 1 1 1 ] 0.2 0.2 1
+}

Objects
{
    $Plane plane1 -1 [ 0 1 0 ] @checker [ 0 0 0 ] [ 1 1 1 ] @specularHardness 4

    $Plane plane2 -5 [ 0 1 -1 ] [ 1 1 0 ] /

    $Sphere sphere1 [ 0 0 2 ] 0.8 [ 1 0 1 ] @specularHardness 5

    $Sphere sphere2 [ -1 1.2 2 ] 0.6 [ 0.1 0.4 0.95 ] @reflective 70;

    $Sphere sphere3 [ 0.9 0.15 2.4 ] 0.3 [ 0 1 0 ] @specularHardness 100

    $Sphere sphere4 [ -0.9 0.15 0.8 ] 0.3 [ 1 0 0 ] @refractive 1.2 100

    $Sphere sphere5 [ 0.5 0.15 0.2 ] 0.2 [ 0 0.8 1 ] @specularHardness 40;
$}

bakup2_______________________________________
NAME "example" DIMENSIONS ["500" "500"]
CAMERA ["0", "1", "-2"] ["0", "0", "6"]
DEPTH "4" ANTI-ALIASING "2"

Lights
{
    +light1 [ 5 5 4 ] [ 0.347 0.89 0.78 ] [ 0.347 0.89 0.78 ] 2 2 1
    +light2 [ -5 5 4 ] [ 1 1 1 ] [ 1 1 1 ] 2 2 1

+}

Objects
{
    $Plane plane1 -1 [ 0 1 0 ] @checker [ 0 0 0 ] [ 1 1 1 ] @specularHardness 4

    $Plane plane2 -5 [ 0 1 -1 ] [ 1 1 0 ] /

    $Sphere sphere1 [ 0 0 2 ] 0.8 [ 1 0 1 ] @specularHardness 5

    $Sphere sphere2 [ -1 1.2 2 ] 0.6 [ 0.1 0.4 0.95 ] @reflective 70;

    $Sphere sphere3 [ 0.9 0.15 2.4 ] 0.3 [ 0 1 0 ] @specularHardness 100

    $Sphere sphere4 [ -0.9 0.15 0.8 ] 0.3 [ 1 0 0 ] @refractive 1.2 100

    $Sphere sphere5 [ 0.5 0.15 0.2 ] 0.2 [ 0 0.8 1 ] @specularHardness 40;
$}

