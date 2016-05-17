#include "O3DModel.h"
#include <vector>
#include "AssetManager.h"
extern GLint u_Model;
extern GLint color_in;
extern GLint u_isTextured;
extern GLuint program;
extern AssetManager* assetManager;
O3DModel::O3DModel(vec3 pos, RotPoint rotcnt, double rotz, double rotx, std::string type, GModel* model)
	:GObject(Rect(pos.x, pos.y, 0, 0), Rect(0, 0, 0, 0), type)
{
	double rcntx, rcnty, rcntz;
	//inits model... just as ORect
	switch (rotcnt) {
	case CENTER:
		rcntx = pos.x;
		rcnty = pos.y;
		rcntz = pos.z;
		break;
	case ORIGIN:
	default:
		rcntx = 0;
		rcnty = 0;
		rcntz = 0;
		break;
	}
	setRotation(rotz, rotx);
	setPos(pos.x, pos.y, pos.z);

	this->model = (*model);
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}

void O3DModel::draw(mat4 MVMatrix) {
	//TODO : implement drawing the 3d model
	GLint error;
	vec4 colors = vec4(r, g, b, 1);
	glEnable(GL_TEXTURE_2D);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, model.getModelID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, model.getUVID());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, model.getVNormalID());
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, model.getFNormalID());
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, model.getTangentID());
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, model.getBiTangentID());
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* when glActeiveTexture(enum) is called,
	 * the next glBindTexture will bind to the 
	 * specified texture unit represented by enum
	 *
	 * In main::init(), get uniform location of sampler2D
	 * and assign the index of texture unit. For example
	 * when enum is GL_TEXTURE0 -> assign 0
	 * GL_TEXTURE0 + 1 -> assign 1
	 * 
	 * For this program, use GL_TEXTURE0 for surface color texture
	 * and GL_TEXTURE0+1 for normal map texture
	 */

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 
		model.getTextureID(GModel::TEXTURE_DIFFUSE));

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D,
		model.getTextureID(GModel::TEXTURE_NORMAL));

	//checks if the normal map is set
	GLint u_isNormaled;
	u_isNormaled = glGetUniformLocation(program, "isNormaled");
	if (model.isTextureSet(GModel::TEXTURE_NORMAL)) {
		glUniform1i(u_isNormaled, 1);
	}
	else {
		glUniform1i(u_isNormaled, 0);
	}

	GLint lightpos1, lightpos2;
	lightpos1 = glGetUniformLocation(program, "LightPosition1");
	lightpos2 = glGetUniformLocation(program, "LightPosition2");
	glUniform3fv(lightpos1, 1, vec3(-5.0, 0.0, 10.0));
	glUniform3fv(lightpos2, 1, vec3(5.0, 0.0, 10.0));

	glUniform4fv(color_in, 1, colors);
	glUniformMatrix4fv(u_Model, 1, true, MVMatrix);
	glUniform1i(u_isTextured, 1);
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexSize());
	glDisable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, model.getModelID());
	error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << glewGetErrorString(error) << std::endl;
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
}
void O3DModel::setColor(int r, int g, int b)
{
	/* ------------------------------------------------------ */
	/* implement converting int rgb to double rgb and storing */
	/* ------------------------------------------------------ */
	this->r = ((double)r / 256.0f);
	this->g = ((double)g / 256.0f);
	this->b = ((double)b / 256.0f);
}

void O3DModel::frameAction() {

}

void O3DModel::setModel(GModel* model) {
	this->model = (*model);
}