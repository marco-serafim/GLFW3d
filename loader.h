#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>


// simple function for loading text files for shader, return the char *shader given the right path.
const char *loadText(const char *textFile){
    FILE *file = fopen(textFile, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }
    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    fclose(file);
    return content;
}

// function to reduce the work necessary to load a glm::mat4 into the shader program.
void loadUniform(unsigned int shaderProgram, const char *uniformName, glm::mat4 matrix){
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}

// function to return the modulum of a number (it's distance to zero in the infinite number line)
float modulum(float number){
    if(number < 0){
        return number * -1;
    }
    else{
        return number;
    }
}