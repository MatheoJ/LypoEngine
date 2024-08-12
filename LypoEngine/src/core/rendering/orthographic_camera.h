//
// Created by mathe on 10/08/2024.
//
#pragma once

namespace Lypo {
    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return position_; }
        void SetPosition(const glm::vec3& position) { position_ = position; RecalculateViewMatrix(); }

        float GetRotation() const { return rotation_; }
        void SetRotation(float rotation) { rotation_ = rotation; RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return projectionMatrix_; }
        const glm::mat4& GetViewMatrix() const { return viewMatrix_; }
        const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix_; }
    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 projectionMatrix_;
        glm::mat4 viewMatrix_;
        glm::mat4 viewProjectionMatrix_;

        glm::vec3 position_ = { 0.0f, 0.0f, 0.0f };
        float rotation_ = 0.0f;


    };
}


