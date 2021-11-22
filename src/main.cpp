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


#include <Filesystem>
#include "Mesh.h"


const GLint WIDTH = 1280, HEIGHT = 720;

Vertex vertices[] =
{//		 COORDINATES	 /		 COLORS		     /   TexCoord    /       NORMALS       //
	Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
};


// Indices for vertices order
GLuint indices[] =
{
	 0, 1, 2,
	 0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES       //
	Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},
	Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
	Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, 0.1f, 0.1f)},
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7,
};



int main()
{
	/**
	*
	*   Initialize GLFW
	* 
	*****************************************/
    
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft??", NULL, NULL);

	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, WIDTH, HEIGHT);

	Texture textures[]
	{
		Texture("src/Textures/terrain.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	/*****************************************
	* 
	*	End Initializing GLFW
	* 
	**/


	/**
	*
	*   Adding Vertex and Shader Linking
	* 
	*****************************************/

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("src/default.vert", "src/default.frag");

	vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh floor(verts, ind, tex);

	/*****************************************
	* 
	*	End Linking
	*
	**/

	/**
	* 
	*	Lighting
	* 
	******************************************/
	
	Shader lightShader("src/light.vert", "src/light.frag");

	vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	glm::vec3 lightPos = glm::vec3(-0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	/*****************************************
	*
	*	End Lighting
	*
	**/

	// for textures not to be drawn wrong 
	glEnable(GL_DEPTH_TEST);

	Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));





	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		camera.Inputs(window);
		camera.updateMatrix(65.0f, 0.1f, 100.0f);

		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
