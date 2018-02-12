
#ifndef YOCTO_UTILS_H
#define YOCTO_UTILS_H

#include "yocto/yocto_gl.h"

namespace voronoi {

    void add_camera(ygl::scene* scn, ygl::string name, ygl::vec3f from,
        ygl::vec3f to = { 0, 1, 0 }, float yfov = 15.0f,
        float aperture = 0, float aspect = 16.0f / 9.0f)
    {
        auto cam = new ygl::camera();
        cam->name = name;
        cam->frame = lookat_frame3f(from, to, { 0, 1, 0 });
        cam->aperture = aperture;
        cam->focus = length(from - to);
        cam->yfov = yfov * ygl::pif / 180;
        cam->aspect = aspect;
        scn->cameras += cam;
    }

    void add_instance(ygl::scene* scn, const std::string& name, ygl::shape* shp, ygl::material* mat,
        const ygl::vec3f& pos = ygl::zero3f, ygl::vec3f rot = ygl::zero3f)
    {
        if (!shp)
            throw ygl::runtime_error("add_instance: shp is null");
        if (!mat)
            throw ygl::runtime_error("add_instance: mat is null");

        // Check if material is already in the scene (if not, add it)
        if (std::find(scn->materials.begin(), scn->materials.end(), mat) == scn->materials.end())
            scn->materials += mat;

        // Check if shape is already in the scene (if not, add it)
        if (std::find(scn->shapes.begin(), scn->shapes.end(), shp) == scn->shapes.end())
            scn->shapes += shp;

        // If there is a texture in the material, check if texture is already in the scene (if not, add it)
        if (mat->kd_txt.txt && std::find(scn->textures.begin(), scn->textures.end(), mat->kd_txt.txt) == scn->textures.end())
            scn->textures += mat->kd_txt.txt;

        // Add material to the shape
        shp->mat = mat;

        // Create instance, calculate frame (from position and rotation), and add to the scene
        auto inst = new ygl::instance();
        inst->name = name;
        inst->shp = shp;
        inst->frame = ygl::frame3f{
            ygl::rotation_mat3f(ygl::vec3f{ 0, 0, 1 }, rot[2] * ygl::pif / 180) *
            ygl::rotation_mat3f(ygl::vec3f{ 0, 1, 0 }, rot[1] * ygl::pif / 180) *
            ygl::rotation_mat3f(ygl::vec3f{ 1, 0, 0 }, rot[0] * ygl::pif / 180),
            pos
        };
        scn->instances += inst;

        // If is a light, add it into its array
        if (mat->ke != ygl::zero3f)
        {
            auto l = new ygl::light();
            l->ist = inst;
            scn->lights += l;
        }
    }

    void add_instance(ygl::scene* scn, const std::string& name, ygl::shape* shp,
        const ygl::vec3f& pos = ygl::zero3f, ygl::vec3f rot = ygl::zero3f)
    {
        if (!shp->mat)
            throw ygl::runtime_error("add_instance: shp->mat is null");

        add_instance(scn, name, shp, shp->mat, pos, rot);
    }

    void add_environment_light(ygl::scene* scn, const std::string& name, ygl::vec3f ke = ygl::zero3f)
    {
        // Create and add environment obj
        auto env = new ygl::environment();
        env->ke = ke;
        scn->environments += env;

        // Create and add the releted light obj
        auto l = new ygl::light();
        l->env = env;
        scn->lights += l;
    }

    ygl::material* make_material(const std::string& name, const ygl::vec3f& kd,
        const ygl::vec3f& ks = { 0.2f, 0.2f, 0.2f }, float rs = 0.01f,
        const ygl::vec3f& ke = ygl::zero3f, ygl::texture* kd_txt = nullptr
    )
    {
        auto mat = new ygl::material();
        mat->name = name;
        mat->kd = kd;
        mat->kd_txt.txt = kd_txt;
        mat->ke = ke;
        mat->ks = ks;
        mat->rs = rs;
        return mat;
    }

    ygl::shape* make_quad(ygl::string name, float side = 1.0f, ygl::material* mat = nullptr)
    {
        if (side <= 0.0f)
            throw ygl::runtime_error("make_quad -> invalid side");

        auto shp = new ygl::shape();
        shp->name = name;
        tie(shp->quads, shp->pos, shp->norm, shp->texcoord) = ygl::make_uvquad(0);
        for (auto& p : shp->pos) p *= side;
        if (mat) shp->mat = mat;
        return shp;
    }

    ygl::shape* make_floor(ygl::string name, float side = 20.0f, ygl::material* mat = nullptr)
    {
        if (side <= 0.0f)
            throw ygl::runtime_error("make_floor -> invalid side");

        auto shp = new ygl::shape();
        shp->name = name;
        tie(shp->quads, shp->pos, shp->norm, shp->texcoord) = ygl::make_uvquad(6);
        for (auto& p : shp->pos) p = { -p.x, p.z, p.y };
        for (auto& n : shp->norm) n = { n.x, n.z, n.y };
        for (auto& p : shp->pos) p *= side;
        for (auto& uv : shp->texcoord) uv *= side;
        if (mat) shp->mat = mat;
        return shp;
    }

    ygl::shape* make_sphere(const std::string& name, float ray = 1.0f, ygl::material* mat = nullptr)
    {
        if (ray <= 0.0f)
            throw ygl::runtime_error("make_sphere -> invalid ray");

        auto shp = new ygl::shape();
        shp->name = name;
        tie(shp->quads, shp->pos, shp->norm, shp->texcoord) = ygl::make_uvsphere(5);
        for (auto& p : shp->pos) p *= ray;
        if (mat) shp->mat = mat;
        return shp;
    }

    // Get 2D point univocal ID
    static inline ygl::string make_id(const ygl::vec2f& p) { return std::to_string(p.x) + ";" + std::to_string(p.y); }
}

#endif