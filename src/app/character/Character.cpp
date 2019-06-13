#include <GL/glew.h>
#include "Character.h"
#include "../utils/utils.h"
#include "../../SOIL2/SOIL2.h"


Character::Character(CharacterState state) : DirectionalAsset() {
    this->direction = state.direction;
}

Character::Character(CharacterState state, const Assets &new_assets) : DirectionalAsset() {
    this->direction = state.direction;
    this->assets = new_assets;
}


void Character::load_and_buffer_asset(const std::string& file_name) {
    if (file_name.empty() || !utils::file_exists(file_name)) {
        return;
    }
#if 0
    int width, height;
    glGenTextures( 1, &this->texture_id );
    glBindTexture( GL_TEXTURE_2D, this->texture_id );
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char *data = SOIL_load_image( file_name.c_str(), &width, &height, nullptr, 1 );
    if (data == nullptr) {
        // todo: indicate that asset loading failed
        return this->texture_id;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
//    glGenerateMipmap(GL_TEXTURE_2D);
//    glGenerateMipmap( GL_TEXTURE_2D );
    SOIL_free_image_data( data );
//    glBindTexture(GL_TEXTURE_2D, 0);
#endif
// load and create a texture
    // -------------------------
    glGenTextures(1, &this->texture_id);
    glBindTexture(GL_TEXTURE_2D, this->texture_id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int cw, ch, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = SOIL_load_image(file_name.c_str(), &cw, &ch, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cw, ch, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    SOIL_free_image_data(data);
}

Character::Character(const std::string &name, const std::string &file_name) : DirectionalAsset() {
    this->character_name = name;
//    this->texture_id = this->load_and_buffer_asset(file_name);
}

void Character::render() {
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glLoadIdentity();
    glTranslatef(this->position.x, this->position.y, 0);
//    glDrawArrays(GL_QUADS, 0, 4);
//    glBindTexture(GL_TEXTURE_2D, 0);
}

Character::~Character() {
    glDeleteTextures(1, &this->texture_id);
}

void Character::setup_directions(GLFWwindow *w) {

//    if (glfwGetKey(w, GLFW_KEY_UP)) {
//        this->change_direction(Direction.UP);
//    }
}
