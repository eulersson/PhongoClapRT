#PBR Application

My programming project will be focused on implementing the ray-tracing algorithm in order to render out images based on the OpenGL pre-visualization viewports. My render application will consider the physical laws and nature of light and its propagation so I could say it would be a PBR (Physically Based Rendering) System. :pray:

##Research
First of all I researched the mathematics behind the ray-tracing algorithm and it's lowest level geometric operations. I also had to refresh my knowledge about integrals and their geometric meaning. I watched some videos on Khan Academy about integrating 1D functions so that I can understand why we need to integrate a surface in order to get the incoming light from around a point of it. After this I searched for the ray-tracing algorithm method and its advantages.

###Raytrace Algorithm


##Workflow
After having investigated I split the different ideas and I put them together into an ordered workflow.

##Initial Ideas
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