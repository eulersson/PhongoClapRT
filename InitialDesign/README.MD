#PBR Application

My programming project will be focused on implementing the ray-tracing algorithm in order to render out images based on the OpenGL pre-visualization viewports. My render application will consider the physical laws and nature of light and its propagation so I could say it would be a PBR (Physically Based Rendering) System.

##Research
<!--First of all I researched the mathematics behind the raytracing algorithm and its lowest level geometric operations. I also had to refresh my knowledge about integrals and their geometric meaning. I watched some videos on Khan Academy about integrating 1D functions so that I can understand why we need to integrate a surface in order to get the incoming light from around a point of it. After this I searched for the ray-tracing algorithm method and its advantages. After I searched how light propagates and why do we see the objects around us.-->
###Light
The light sources emit energy particles which are called photons, they consist on a magnetic and electric fields oscillating. When they hit a surface various things could happen depending on its material. There are different properties on materials, they bounce light in many different ways. When light hits the surface a part of it gets absorbed by the material (it doesn't disappear, it simply gets transformed into heat or other energy manifestations). This energy that gets absorbed is referred as *Transimittance*, and it will depend on the quality of the material, darker colours for instance absorb more light, that's why it's not cool wearing black cloths in a sunny day in summer :nogood:. The initial light energy minus the transmittance is what is left and keeps traveling into another direction, defined by the reflection law.

![Reflection](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/reflection.png)

Refraction is another important phenomenon to consider. Some materials allow light pass through them, light is deviated by a certain angle which varies depending on the properties of the material. The light ray is also deviated when it exits the object. Every time the medium changes, the ray varies its direction.


###Raytrace Algorithm
The way light is calculated on computers differ a little bit from the natural phenomenon for efficiency reasons. The raytrace algorithm is one of the most popular methods for simulating the light behaviour on computer graphics. It has a special characteristic and this is that it is known to be a backward tracing process. We don't calculate all the directions in which light travels and emits the bounced colours of materials... Instead, we just focus on one point of view, our eye point of view. Then we project some rays alongside some samples on a specific pixel and calculate if there is any intersection.
![Raytracing](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/raytracing.png)



##Class Design
###Sketch
![Class Diagram Sketch](https://github.com/NCCA/docwhite-CA1/blob/master/InitialDesign/class_diagram_sketch.png)
I tried to write down all the classes I might need. This is a very rough approximation. I 

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