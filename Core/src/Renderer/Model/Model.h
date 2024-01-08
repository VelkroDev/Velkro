#include "Mesh.h"

#include "../FileManager/FileInput.h"

#include <JSON/json.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

using json = nlohmann::json;

namespace Velkro
{
	class Model
	{
	public:
		Model()
		{
		}

		Model(const char* filePath, TextureMipMap mipmapType, json json)
		{
			m_JSON = json;

			m_FilePath = filePath;

			m_Data = GetData();
						
			for (int i = 0; i < m_JSON["meshes"].size(); i++)
			{
				TraverseNode(i, mipmapType);
			}			
		}

		~Model()
		{
		}

		static Model CreateModel(const char* filePath, TextureMipMap mipmapType = VLK_LINEAR)
		{
			FileInput file = FileInput::CreateFileInput(filePath);
			json json = json::parse(file.GetInput());

			return Model(filePath, mipmapType, json);
		}

		void Render(Shader& shader)
		{
			// Go over all meshes and render each one
			for (unsigned int i = 0; i < m_Meshes.size(); i++)
			{
				glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), Position);
				glm::mat4 rotationMat    = glm::mat4_cast(glm::quat(Rotation));
				glm::mat4 scaleMat       = glm::scale(glm::mat4(1.0f), Scale);

				m_Meshes[i].Mesh::Render(shader, translationMat * rotationMat * scaleMat * m_MatricesMeshes[i]);
			}
		}

		void SetPosition(glm::vec3 position)
		{
			Position = position;
		}

		void SetScale(glm::vec3 scale)
		{
			Scale = scale;
		}

		void SetRotation(glm::vec3 rotation)
		{
			Rotation = rotation;
		}

		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		
	private:
		void LoadMesh(unsigned int indMesh, TextureMipMap mipmapType)
		{
			unsigned int posAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
			unsigned int normalAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
			unsigned int texAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
			unsigned int colAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["material"];
			unsigned int indAccInd = m_JSON["meshes"][indMesh]["primitives"][0]["indices"];

			std::vector<float> posVec = GetFloats(m_JSON["accessors"][posAccInd]);
			std::vector<glm::vec3> positions = GroupFloatsVec3(posVec);
			std::vector<float> normalVec = GetFloats(m_JSON["accessors"][normalAccInd]);
			std::vector<glm::vec3> normals = GroupFloatsVec3(normalVec);
			std::vector<float> texVec = GetFloats(m_JSON["accessors"][texAccInd]);
			std::vector<glm::vec2> texUVs = GroupFloatsVec2(texVec);

			std::vector<Vertex> vertices = AssembleVertices(positions, normals, texUVs);
			std::vector<GLuint> indices = GetIndices(m_JSON["accessors"][indAccInd]);
			std::vector<Texture> textures = GetTextures(mipmapType);

			m_Meshes.push_back(Mesh::CreateMesh(vertices, indices, textures));
		}

		void TraverseNode(unsigned int nextNode, TextureMipMap mipmapType, glm::mat4 matrix = glm::mat4(1.0f))
		{
			json node = m_JSON["nodes"][nextNode];

			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
			if (node.find("translation") != node.end())
			{
				float transValues[3];
				for (unsigned int i = 0; i < node["translation"].size(); i++)
					transValues[i] = (node["translation"][i]);
				translation = glm::make_vec3(transValues);
			}

			glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
			if (node.find("rotation") != node.end())
			{
				float rotValues[4] =
				{
					node["rotation"][3],
					node["rotation"][0],
					node["rotation"][1],
					node["rotation"][2]
				};
				rotation = glm::make_quat(rotValues);
			}

			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
			if (node.find("scale") != node.end())
			{
				float scaleValues[3];
				for (unsigned int i = 0; i < node["scale"].size(); i++)
					scaleValues[i] = (node["scale"][i]);
				scale = glm::make_vec3(scaleValues);
			}

			glm::mat4 matNode = glm::mat4(1.0f);
			if (node.find("matrix") != node.end())
			{
				float matValues[16];
				for (unsigned int i = 0; i < node["matrix"].size(); i++)
					matValues[i] = (node["matrix"][i]);
				matNode = glm::make_mat4(matValues);
			}

			glm::mat4 trans = glm::mat4(1.0f);
			glm::mat4 rot = glm::mat4(1.0f);
			glm::mat4 sca = glm::mat4(1.0f);

			trans = glm::translate(trans, translation);
			rot = glm::mat4_cast(rotation);
			sca = glm::scale(sca, scale);

			glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

			if (node.find("mesh") != node.end())
			{
				m_TranslationsMeshes.push_back(translation);
				m_RotationsMeshes.push_back(rotation);
				m_ScalesMeshes.push_back(scale);
				m_MatricesMeshes.push_back(matNextNode);

				LoadMesh(node["mesh"], mipmapType);
			}

			if (node.find("children") != node.end())
			{
				for (unsigned int i = 0; i < node["children"].size(); i++)
					TraverseNode(node["children"][i], mipmapType, matNextNode);
			}
		}

		std::vector<unsigned char> GetData()
		{
			std::string bytesText;
			std::string uri = m_JSON["buffers"][0]["uri"];
			
			// The data is in a separate .bin file
			std::string fileStr = std::string(m_FilePath);
			std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

			FileInput file = FileInput::CreateFileInput(fileDirectory + uri);

			bytesText = file.GetInput();

			std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
			return data;
		}

		std::vector<float> GetFloats(json accessor)
		{
			std::vector<float> floatVec;

			unsigned int buffViewInd = accessor.value("bufferView", 1);
			unsigned int count = accessor["count"];
			unsigned int accByteOffset = accessor.value("byteOffset", 0);
			std::string type = accessor["type"];

			json bufferView = m_JSON["bufferViews"][buffViewInd];
			unsigned int byteOffset = bufferView.value("byteOffset", 0);

			unsigned int numPerVert;
			if (type == "SCALAR") numPerVert = 1;
			else if (type == "VEC2") numPerVert = 2;
			else if (type == "VEC3") numPerVert = 3;
			else if (type == "VEC4") numPerVert = 4;
			else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

			unsigned int beginningOfData = byteOffset + accByteOffset;
			unsigned int lengthOfData = count * 4 * numPerVert;
			for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i)
			{
				unsigned char bytes[] = { m_Data[i++], m_Data[i++], m_Data[i++], m_Data[i++] };
				float value;
				std::memcpy(&value, bytes, sizeof(float));
				floatVec.push_back(value);
			}

			return floatVec;
		}

		std::vector<GLuint> GetIndices(json accessor)
		{
			std::vector<GLuint> indices;

			unsigned int buffViewInd = accessor.value("bufferView", 0);
			unsigned int count = accessor["count"];
			unsigned int accByteOffset = accessor.value("byteOffset", 0);
			unsigned int componentType = accessor["componentType"];

			json bufferView = m_JSON["bufferViews"][buffViewInd];
			unsigned int byteOffset = bufferView["byteOffset"];

			unsigned int beginningOfData = byteOffset + accByteOffset;
			if (componentType == 5125)
			{
				for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
				{
					unsigned char bytes[] = { m_Data[i++], m_Data[i++], m_Data[i++], m_Data[i++] };
					unsigned int value;
					std::memcpy(&value, bytes, sizeof(unsigned int));
					indices.push_back((GLuint)value);
				}
			}
			else if (componentType == 5123)
			{
				for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
				{
					unsigned char bytes[] = { m_Data[i++], m_Data[i++] };
					unsigned short value;
					std::memcpy(&value, bytes, sizeof(unsigned short));
					indices.push_back((GLuint)value);
				}
			}
			else if (componentType == 5122)
			{
				for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
				{
					unsigned char bytes[] = { m_Data[i++], m_Data[i++] };
					short value;
					std::memcpy(&value, bytes, sizeof(short));
					indices.push_back((GLuint)value);
				}
			}

			return indices;
		}

		std::vector<Texture> GetTextures(TextureMipMap mipmapType)
		{
			std::vector<Texture> textures;

			std::string fileStr = std::string(m_FilePath);
			std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

			for (unsigned int i = 0; i < m_JSON["images"].size(); i++)
			{
				std::string texPath = m_JSON["images"][i]["uri"];

				bool skip = false;
				for (unsigned int j = 0; j < m_LoadedTexName.size(); j++)
				{
					if (m_LoadedTexName[j] == texPath)
					{
						textures.push_back(m_LoadedTex[j]);
						skip = true;
						break;
					}
				}

				if (!skip)
				{
					bool isDiffuseTexture = false;
					for (const auto& material : m_JSON["materials"])
					{
						if (material["pbrMetallicRoughness"]["baseColorTexture"].contains("index"))
						{
							int index = material["pbrMetallicRoughness"]["baseColorTexture"]["index"];
							if (index == i)
							{
								isDiffuseTexture = true;
								break;
							}
						}
					}

					if (isDiffuseTexture)
					{
						Texture diffuse = Texture2D::CreateTexture((fileDirectory + texPath).c_str(), mipmapType, VLK_REPEAT, VLK_DIFFUSE);
						textures.push_back(diffuse);
						m_LoadedTex.push_back(diffuse);
						m_LoadedTexName.push_back(texPath);
					}
					else
					{
						Texture specular = Texture2D::CreateTexture((fileDirectory + texPath).c_str(), mipmapType, VLK_REPEAT, VLK_SPECULAR);
						textures.push_back(specular);
						m_LoadedTex.push_back(specular);
						m_LoadedTexName.push_back(texPath);
					}
				}
			}

			return textures;
		}

		std::vector<Vertex> AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> texUVs)
		{
			std::vector<Vertex> vertices;
			for (int i = 0; i < positions.size(); i++)
			{
				vertices.push_back(Vertex(positions[i], normals[i], glm::vec3(0.0f, 0.0f, 0.0f), texUVs[i]));
			}

			return vertices;
		}


		std::vector<glm::vec2> GroupFloatsVec2(std::vector<float> floatVec)
		{
			std::vector<glm::vec2> vectors;
			for (int i = 0; i < floatVec.size(); i)
			{
				vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
			}
			return vectors;
		}
		std::vector<glm::vec3> GroupFloatsVec3(std::vector<float> floatVec)
		{
			std::vector<glm::vec3> vectors;
			for (int i = 0; i < floatVec.size(); i)
			{
				vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
			}
			return vectors;
		}
		std::vector<glm::vec4> GroupFloatsVec4(std::vector<float> floatVec)
		{
			std::vector<glm::vec4> vectors;
			for (int i = 0; i < floatVec.size(); i)
			{
				vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
			}
			return vectors;
		}

		const char* m_FilePath;
		std::vector<unsigned char> m_Data;
		json m_JSON;

		std::vector<Mesh> m_Meshes;
		std::vector<glm::vec3> m_TranslationsMeshes;
		std::vector<glm::quat> m_RotationsMeshes;
		std::vector<glm::vec3> m_ScalesMeshes;
		std::vector<glm::mat4> m_MatricesMeshes;

		std::vector<std::string> m_LoadedTexName;
		std::vector<Texture> m_LoadedTex;
	};
}