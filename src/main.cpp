// Authors: 
// Sylvia and Aven
// 
// GitHub: 
// https://github.com/sylvsyntax/minecraft-GLSL


// SOURCES
// 
// 
// Setup of GLFW, OpenGL, and most of the dependencies:
// https://www.youtube.com/watch?v=45MIykWJ-C4
// Setting up GLM for matrices in c++:
// https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites


#include "Mesh.h"
#include "World.h"


const GLint WIDTH = 1280, HEIGHT = 720;



int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft??", nullptr, nullptr);

    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, WIDTH, HEIGHT);
    

    // for textures not to be drawn wrong
    // Enables the depth test so faces drawn behind objects won't overlap.
    glEnable(GL_DEPTH_TEST);

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
    

    World minecraft;
    
    //int curxChunk = -1, curyChunk = -1;

    //bool generating = false;
    //int ie = 0;
    
    double prevTime = glfwGetTime();
    
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double curTime = glfwGetTime();
        if(curTime - prevTime >= 1/60){
            minecraft.worldTime = curTime;
            prevTime = curTime;
        }
        //minecraft.updateSpecial();
		camera.Inputs(window);
		camera.updateMatrix(65.0f, 0.1f, 100.0f);
        cout << "Total Chunks: " << minecraft.chunks.size() << "\n\n";

        for (auto & i : minecraft.sceneMeshes)
        {
            i.Draw(minecraft.shaderProgram, camera);
        }
        for (auto & i : minecraft.sceneLights)
        {
            i.Draw(minecraft.lightShader, camera);
        }
        

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	minecraft.shaderProgram.Delete();
	minecraft.lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
