#PBR Application

My programming project will be focused on implementing the ray-tracing algorithm in order to render out images based on the OpenGL pre-visualization viewports. My render application will consider the physical laws and nature of light and its propagation so I could say it would be a PBR (Physically Based Rendering) System.

##Research
###Light
The light sources emit energy particles which are called photons, they consist on a magnetic and electric fields oscillating one perpendicularly to each other. When they hit a surface various things could happen depending on its material. There are different properties on materials, they bounce light in many different ways. When light hits the surface a part of it gets absorbed by the material (it doesn't disappear, it simply gets transformed into heat or other energy forms). This energy that gets absorbed is referred as *Transmittance*, and it will depend on the quality of the material, darker colours for instance absorb more light, that's why it's not cool wearing black cloths in a sunny day in summer :no_good:. The initial light energy minus the transmittance is what is left it gets scattered into another direction, defined by the reflection law.

![Reflection](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/reflection.png)

Refraction is another important phenomenon to consider. Some materials allow light pass through them due to their electronic configuration (dielectric materials), light is deviated by a certain angle which varies depending on the properties of the material. The light ray is also deviated when it exits the object. Every time the medium changes, the ray varies its direction.

![Refraction](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/refraction.png)

###Raytrace Algorithm
The way light is calculated on computers differ a little bit from the natural phenomenon for efficiency reasons. The raytrace algorithm is one of the most popular methods for simulating the light behaviour on computer graphics. 

![Raytracing](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/raytracing.png)

It has a special characteristic and this is that it is known to be a backward tracing process. We don't calculate all the directions in which light travels and emits the bounced colours of materials... Instead, we just focus on one point of view, our eye point of view. Then we project some rays alongside some samples on a specific pixel and calculate if there is any intersection. If the ray intersects with an object then, from this intersected point we throw some secondary rays called *Shadow Rays* which are directed towards all the different lights in the scene. If the shadow ray does not collide with any other object it means that there are no obstacles between the light and the collision point on surface, so we will calculate the light contribution to the point according to the light properties (such as angle, decay, attenuation) and the material qualities (such as BRDF) and the orientation of the face in relation to the eye (cosine term, Fresnel effect).

In order to calculate this amount of light precisely there is an specific formula: the **Rendering Equation**, which I will explain in the following image:

![Rendering Equation](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/rendering_equation.png)

It's important to know that if the surface is reflective we would need to repeat the process firing a ray from the hit point towards the reflected direction. A recursive call would be needed, thus we would need to set a maximum depth for avoiding infinite loops.

In the next section I will talk about how I think I would implement this method and which steps should the user follow.

##Class Design
###Sketch
I tried to write down all the classes I might need. This is a very rough approximation. I am sure I will need some more, but I still don't know which kind of them yet. I will be finding them out on the go.

![Class Diagram Sketch](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/class_diagram_sketch.png)

How will data flow through my program? Let me enumerate the fundamental steps:

1. **PARSING** and **GUI Initialisation**: In the main body a Scene object will be instantiated and will be initialized with information about the input geometry file specified by the user. I still don't know which method would be the most suitable, I thought *.obj* files could be a good choice because they are widely accepted by 3D packages, but I will have to take a look at how they are written and how to break down the objects they include. I will probably use the *Obj* C++ class provided in the NGL library. The geometry will be stored under *Shape* objects which will be all gathered together under the *all_primitives* attribute container in the *Scene* object. Same with the lights, all the lights will be cached into the *Scene* light container. If the user doesn't load a file we could implement an interface to add and translate objects and light from scratch, but very simple primitives. After this we will initialise every single Graphics User Interface module, including all the viewports.

2. Once parsing and initialising have been successful we give way to the user to tweak some parameters. These can be object attributes, or camera settings. As we mentioned earlier we allow the user to add more elements into the scene. No rendering will be done until user configures rendering parameters and hits render.

3. Now the **RENDER LOOP** starts. A *Renderer* object is created. The members of this class' object are a sampler, a camera, a surface integrator and a film. And its methods will be the incident light calculator on a certain pixel in the image (Li method), the amount of absorbed light (Transmitance) and a last one to send it to a film object.

   * The Sampler will generate some random numbers that will be used for tracing a ray that will pierce the current pixel on a random point along its area. The user will be able to choose how many samples per pixel s/he wants to use.

   * The Camera will be used with the sampler to know where to fire the ray from.

   * The SurfaceIntegrator will have an intersection object (or maybe I will use a data structure instead). We will call the Scene method "Intersect" and we will pass the ray we got which origin is given by the camera position and which direction given by the sampler and will check it it collides with any object. In case it does we will be able to access the Intersection object which will contain the collision point.

   * Still in the SurfaceIntegrator object we will iterate through all the lights and calculate the incoming radiance on this point from each light. We will do so by throwing shadow rays. The *Li* function in *SurfaceIntegrator* will give us the final radiance on the fired point. After this is done, the value is returned to the renderer and kept in an array of samples. The process is repeated in the current pixel for whatever amount of samples the user has specified. After the array of samples has been filled out we call a method in the *Pixel* class to average the samples.

   * The Film object holds all the pixels and reference to the image we will need to write to. It receives the final radiance for each pixel (not sampled yet!) and stores it into the samples array we mentioned before, which is located in the Pixel objects. Once the radiance is averaged it is stored into the colour member of the pixel and will be written later to the final image.


4. Finally we can use a stream operator to write out all the pixel values into an image container. I learnt how to construct bitmaps in the past, I learned how to write the header files for them and so, but I would prefer to use an industry standard format, such as *.exr* and be able to understand the way we can fill them with information and even learn how to create different passes in the same file. So I will read about the OpenEXR project in the future.

###Extra Features
These are bonus I would try to implement if I have enough time.
* Depth Of Field Blur
* Global Illumination
* Ambient Occlusion
* Exporting Z-Depth

###Dependencies
Other packages and libraries I will use for my project:
* **OpenGL** (via **NGL**) for real-time pre-vis
* **Qt** for GUI management
* **SDL2** for user inputs
* **OpenEXR** for writing output files


##UI and Interaction
The main design idea for the UI is quite simple. I would like to use a 4 viewport window which the user will be able to maximaze as Maya does, and a bar on the right hand side for changing parameters for the objects, cameras, and finally render settings.

##Bibliography
Pharr, M. and Humphreys, G., 2010. *Physically Based Rendering*. Burlington: Morgan Kaufmann Publishers