/* 
 * File:   Particle.h
 * Author: marco
 *
 * Created on February 23, 2011, 3:35 PM
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include <vector>

#define HCUT 6.58211899E-25 // GeV sec

class Particle {
public:
    Particle() {};
    Particle(double mass, double width);
    Particle(const Particle& orig);
    virtual ~Particle() {};
    /**
     * 
     * @return the particle mass in GeV
     */
    double getMass() const {
        return mass;
    }

    /**
     * set the particle mass
     * @param mass the particle mass in GeV
     */
    void setMass(double mass) {
        this->mass = mass;
    }

    /**
     *
     * @return the particle width in GeV
     */
    double getWidth() const {
        return width;
    }

    /**
     * set the particle width
     * @param width the particle width in GeV
     */
    void setWidth(double width) {
        this->width = width;
    }

protected:
    double mass, width;
};

#endif	/* PARTICLE_H */