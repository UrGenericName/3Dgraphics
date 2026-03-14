# Static 3D Graphics Library Built in C++
WARNING: This is a personal study, do not expect the flexibility or reliability to be anywhere near existing 3D graphics libraries; use Vulkan, Directx, OpenGl etc.

![Blender Monkey Render](https://marius-arcay.netlify.app/icons/project_3d_graphics.jpg)

__Key-features:__
- scene, mesh and shader architecture,
- multi-threading,
- OBJ importer

# Documentation
## Creating and Rendering a Scene

In order to generate and render a basic scene, you need to create to first create a scene object, any mesh objects you'd like to add the scene, and a camera object.  The scene object will store data for which meshes are used, and the camera object stores the method which renders the scene 
```cpp
// Create scene
Scene scene;

// Create camera
Point camPoint(x, y, z);
Angle camAngle(pitch, yaw, roll);
float camFOV = fovInRad;
Camera camera(camPoint, camAngle, camFOV);

// Create our meshes
Mesh cube;
generateCube(cube);
scene.meshCollection.push_back(cube);

// Call method to render camera in window
camera.renderCamera(SCREEN_WIDTH, SCREEN_HEIGHT, scene);
```
<br>

## Scene Class
### Public Member variables
```cpp
bool renderGrid;
unsigned int backgroundColor;
std::vector<Mesh> meshCollection;
```
### Public Methods
```cpp
bool isValid() const;
```

<br>

## Camera Class
### Public Member variables
```cpp
Point position;
Angle rotation;
value_type FOV;
```
### Public Methods
```cpp
bool isValid() const;
void renderCamera(int screenWidth, int screenHeight, Scene& scene);
```
<br>

## Mesh Class
### Public Member variables
```cpp
Point position;
Angle rotation;
float scale;
Material material;
std::vector<Polygon> polygonCollection;
```
### Public Methods
```cpp
bool isValid() const;
```

<br>

## Polygon Class
### Public Methods
```cpp
bool isValid() const;
Point getPointA();
Point getPointB();
Point getPointC();
void newPointA(Point& point_input);
void newPointB(Point& point_input);
void newPointC(Point& point_input);
bool intersectionPoint(const Line& line_input, Point& point_output, double* t_output = nullptr) const;
Vector* normalVector() const;
```

### Additional Shape Presets (Not part of Polygon Class)
```cpp
	void generateCube(Mesh& mesh_input);
	void generatePyramid(Mesh& mesh_input);
	void generateCylinder(Mesh& mesh_input);
	void generateMonkey(Mesh& mesh_input);
```
