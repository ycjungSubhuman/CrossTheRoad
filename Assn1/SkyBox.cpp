#include "SkyBox.h"
#include "TextureCube.h"
#include "AssetManager.h"
#include "Rect.h"

extern GLint u_Model, u_isSkyBox;
extern AssetManager* assetManager;

SkyBox::SkyBox(std::string px, std::string nx, std::string py, std::string ny, std::string pz, std::string nz)
	:GObject(Rect(0,0,0,0), Rect(0,0,0,0), "SKYBOX")
{
	TextureCube tex_cube = TextureCube(px, nx, py, ny, pz, nz);
	buffer_tex = tex_cube.getID();
}
void SkyBox::draw(mat4 MVMatrix) {
	GLint error;
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glDepthMask(GL_FALSE);

	//set flag
	glUniform1i(u_isSkyBox, 1);

	//texture loaded
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, buffer_tex);

	//bind box model
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, assetManager->getModel("box")->getModelID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	error = glGetError();


	//MVMatrix
	glUniformMatrix4fv(u_Model, 1, true, MVMatrix);
	//glUniformMatrix4fv(u_Model, 1, true, vec4());
	error = glGetError();

	//draw
	glDrawArrays(GL_TRIANGLES, 0, 
		assetManager->getModel("box")->getVertexSize());
	error = glGetError();

	glDisableVertexAttribArray(0);
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDepthMask(GL_TRUE);
	glUniform1i(u_isSkyBox, 0);
}
void SkyBox::frameAction() {

}
