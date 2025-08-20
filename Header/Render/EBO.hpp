#pragma once
#include "glad/glad.h" // or your GL loader that defines the GL* types
#include <cstddef>     // for std::nullptr_t / offsetof if you use it

namespace Engine::Render {

    class EBO {
    public:
        EBO();  // glCreateBuffers
        EBO(const void* indices, GLsizeiptr sizeBytes, GLenum usage); // create+upload
        ~EBO() noexcept;

        EBO(const EBO&) = delete;
        EBO& operator=(const EBO&) = delete;

        EBO(EBO&& other) noexcept : m_ID(other.m_ID) { other.m_ID = 0; }
        EBO& operator=(EBO&& other) noexcept {
            if (this != &other) {
                Delete();
                m_ID = other.m_ID;
                other.m_ID = 0;
            }
            return *this;
        }

      
        void SetData(const void* indices, GLsizeiptr sizeBytes, GLenum usage) const;

      
        void Bind()   const; 
        void Unbind() const; 

        void Delete();       

        GLuint GetID() const { return m_ID; }

    private:
        GLuint m_ID = 0;
    };

} // namespace Engine::Render
