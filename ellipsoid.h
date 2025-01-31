//
// Created by zcy on 2021/12/25.
//

#ifndef PICTURES2_ELLIPSOID_H
#define PICTURES2_ELLIPSOID_H

#include "hittable.h"
#include "vec3.h"

class ellipsoid : public hittable{
public:
    ellipsoid(){}

    ellipsoid(point3 cen, double x, double y, double z, shared_ptr<material> m)
        :center(cen), a(x), b(y), c(z), mat_ptr(m) {};

    virtual bool hit(
            const ray &r, double t_min, double t_max, hit_record &rec) const override;

public:
    point3 center;
    double a;
    double b;
    double c;
    shared_ptr<material> mat_ptr;
};

bool ellipsoid::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {

    vec3 tmp1,tmp2;
    tmp1=r.origin(),tmp2=r.direction();
    inverseMatrix(center,tmp1,tmp2,a,b,c);

    auto a = tmp2.length_squared();
    auto half_b = dot(tmp1,tmp2);
    auto c = tmp1.length_squared()-1;

    auto discriminant = half_b*half_b-a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 elli_normal(2*rec.p.x()/(a*a),2*rec.p.y()/(b*b),2*rec.p.z()/(c*c));
    if(dot(r.direction(),elli_normal)<0)
        elli_normal=-1*elli_normal;
    vec3 outward_normal = unit_vector(elli_normal);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    return true;
}



#endif //PICTURES2_ELLIPSOID_H
