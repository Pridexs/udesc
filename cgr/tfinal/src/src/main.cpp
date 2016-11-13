#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

GLFWwindow* window;

#include "shader.h"
#include "texture.h"
#include "controls.h"
#include "objloader.h"

int main() {
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    // 4x Antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // For MacOS... Nao muito util para outros OSs
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Nao usar OpenGL antigo
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    
    window = glfwCreateWindow( 1024, 768, "Trabalho Final - CGR - 2016/2", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Erro ao abrir GLFW window.\n" );
        glfwTerminate();
        return -1;
    }

    // Inicializar GLEW
    glfwMakeContextCurrent(window);

    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test (Z-Buffer)
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Criar e compilar as Shaders
    GLuint programID = loadShaders( "shaders/SimpleVertexShader.vert", "shaders/SimpleFragmentShader.frag" );

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    GLuint textureID  = glGetUniformLocation(programID, "myTextureSampler");
    glUniform1i(textureID, 0);

    GLuint textureRua = loadDDS("textures/rua.DDS");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureRua);

    GLuint textureBoneco = loadDDS("textures/boneco.DDS");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBoneco);

    // Read our .obj file
	std::vector<glm::vec3> vert_rua;
	std::vector<glm::vec2> uvs_rua;
	std::vector<glm::vec3> normals_rua;
	std::vector<unsigned short> indices_rua;

    std::vector<glm::vec3> vert_boneco;
	std::vector<glm::vec2> uvs_boneco;
	std::vector<glm::vec3> normals_boneco;
	std::vector<unsigned short> indices_boneco;

	bool res = loadAssImp("objects/rua.obj", indices_rua, vert_rua, uvs_rua, normals_rua);
    res = loadAssImp("objects/boneco.obj", indices_boneco, vert_boneco, uvs_boneco, normals_boneco);

    GLuint vertexBuffer_rua;
	glGenBuffers(1, &vertexBuffer_rua);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_rua);
	glBufferData(GL_ARRAY_BUFFER, vert_rua.size() * sizeof(glm::vec3), &vert_rua[0], GL_STATIC_DRAW);

	GLuint uvbuffer_rua;
	glGenBuffers(1, &uvbuffer_rua);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_rua);
	glBufferData(GL_ARRAY_BUFFER, uvs_rua.size() * sizeof(glm::vec2), &uvs_rua[0], GL_STATIC_DRAW);

    GLuint vertexBuffer_boneco;
	glGenBuffers(1, &vertexBuffer_boneco);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_boneco);
	glBufferData(GL_ARRAY_BUFFER, vert_boneco.size() * sizeof(glm::vec3), &vert_boneco[0], GL_STATIC_DRAW);

	GLuint uvbuffer_boneco;
	glGenBuffers(1, &uvbuffer_boneco);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_boneco);
	glBufferData(GL_ARRAY_BUFFER, uvs_boneco.size() * sizeof(glm::vec2), &uvs_boneco[0], GL_STATIC_DRAW);


    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

        glm::mat4 ModelMatrix_boneco = ModelMatrix;
        glm::mat4 mvp_boneco = ProjectionMatrix * ViewMatrix * ModelMatrix_boneco;
        
        /** RUA **/
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureRua);

        // 1rst attribute buffer : vert_rua
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_rua);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : uvs_rua
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_rua);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vert_rua.size() );

        glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
        /** END RUA **/

        /** BONECO **/
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp_boneco[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureBoneco);
        glUniform1i(textureID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_boneco);
		glVertexAttribPointer(
			0,                  // attribute		// 2nd attribute buffer : uvs_rua
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_boneco);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vert_boneco.size() );

        glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

        /** END BONECO **/

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
    // glDeleteBuffers(1, &vertexBuffer_rua);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
