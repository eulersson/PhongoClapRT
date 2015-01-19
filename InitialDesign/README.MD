#PBR Application

My programming project will be focused on implementing the ray-tracing algorithm in order to render out images based on the OpenGL pre-visualization viewports. My render application will consider the physical laws and nature of light and its propagation so I could say it would be a PBR (Physically Based Rendering) System.

##Research
###Light
The light sources emit energy particles which are called photons, they consist on a magnetic and electric fields oscillating one perpendicular to each other. When they hit a surface various things could happen depending on its material. There are different properties on materials, they bounce light in many different ways. When light hits the surface a part of it gets absorbed by the material (it doesn't disappear, it simply gets transformed into heat or other energy manifestations). This energy that gets absorbed is referred as *Transmittance*, and it will depend on the quality of the material, darker colours for instance absorb more light, that's why it's not cool wearing black cloths in a sunny day in summer :no_good:. The initial light energy minus the transmittance is what is left and keeps traveling into another direction, defined by the reflection law.

![Reflection](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/reflection.png)

Refraction is another important phenomenon to consider. Some materials allow light pass through them, light is deviated by a certain angle which varies depending on the properties of the material. The light ray is also deviated when it exits the object. Every time the medium changes, the ray varies its direction.


###Raytrace Algorithm
The way light is calculated on computers differ a little bit from the natural phenomenon for efficiency reasons. The raytrace algorithm is one of the most popular methods for simulating the light behaviour on computer graphics. 

![Raytracing](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/raytracing.png)

It has a special characteristic and this is that it is known to be a backward tracing process. We don't calculate all the directions in which light travels and emits the bounced colours of materials... Instead, we just focus on one point of view, our eye point of view. Then we project some rays alongside some samples on a specific pixel and calculate if there is any intersection. If the ray intersects with an object then, from this intersected point we throw some secondary rays called *Shadow Rays* which are directed towards all the different lights in the scene. If the shadow ray does not collide with any other object it means that there are no obstacles between the light and the collision point on surface, so we will calculate the light contribution to the point according to the light properties (such as angle, decay, attenuation) and the material qualities (such as BRDF) and the orientation of the face in relation to the eye (cosine term, Fresnel effect).

In order to calculate this amount of light precisely there is an specific formula: the **Rendering Equation**, which I will explain in the following image:

![Rendering Equation](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/rendering_equation.png)

In the next section I will talk about how I think I would implement this method and which steps should the user follow.

##Class Design
###Sketch
I tried to write down all the classes I might need. This is a very rough approximation. I am sure I will need some more, but I still don't know which kind of them yet. I will be finding them out on the go.

![Class Diagram Sketch](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/class_diagram_sketch.png)

How will data flow through my program? Let me enumerate the fundamental steps:

1. **PARSING** and **GUI Initialisation**: In the main body a Scene object will be instantiated and will be initialized with information about the input geometry file specified by the user. I still don't know which method would be the most suitable, I thought *.obj* files could be a good choice because they are widely accepted by 3D packages, but I will have to take a look at how they are written and how to break down the objects they include. The geometry will be stored under *Shape* objects which will be all gathered together under the *all_primitives* attribute container in the *Scene* object. Same with the lights, all the lights will be cached into the *Scene* light container. If the user doesn't load a file we could implement an interface to add and translate objects and light from scratch, but very simple primitives. After this we will initialise every single Graphics User Interface module, including all the viewports.
2. Once parsing and initialising have been successful we give way to the user to tweak some parameters. These can be object attributes, or camera settings. As we mentioned earlier we allow the user to add more elements into the scene. No rendering will be done until user configures rendering parameters and hits render.
3. Now the **Render Loop is Initialised** [to be continued...]

###Extra Features
These are bonus I would try to implement if I have enough time.
* Depth Of Field Blur
* Exporting Z-Depth

###Dependencies
Other packages and libraries I will use for my project:
* **OpenGL** (via **NGL**) for real-time pre-vis
* **Qt** for GUI management
* **SDL2** for user inputs
* **OpenEXR** for writing output files


##UI and Interaction

##Bibliography
Pharr, M. and Humphreys, G., 2010. *Physically Based Rendering*. Burlington: Morgan Kaufmann Publishers