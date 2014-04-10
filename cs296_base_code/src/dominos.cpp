/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/
#include <iostream>
#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 

  dominos_t::dominos_t()
  {
		//! creates ground
            b2Body* ground = m_world->CreateBody(&bd);
            edge.Set(b2Vec2(-70.0f, -4.5f), b2Vec2(70.0f, -4.5f));
            b2FixtureDef fd;
            fd.shape = &edge;
            ground->CreateFixture(&fd);
       
 		//! shape for crank in the wheel
                shape.SetAsBox(2.0f, 0.5f);
 		//! shape for circle in the wheel
                shape1.m_p.Set(-2.0f, 0.0f); //! relative position of the circles
                shape1.m_radius = 9.5f;
                bd.type = b2_dynamicBody;
                bd.position.Set(-2.0f, 5.0f);
		//! second wheel
                b2Body* secondWheel = m_world->CreateBody(&bd);
		fixtureDef.shape = &shape1;
		fixtureDef.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
		fixtureDef.friction=0;
		secondWheel->CreateFixture(&fixtureDef);
		secondWheel->CreateFixture(&shape, 2.0f);
                //! a fake invisible object to support a revolute joint            
                fake.position.Set(-4.0f, 5.0f);
                b2Body* fakeBody = m_world->CreateBody(&fake);
		//! first wheel
                bd.position.Set(-32.0f, 5.0f);
                b2Body* firstWheel = m_world->CreateBody(&bd);
		fixtureDef.shape = &shape1;
		fixtureDef.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
		fixtureDef.friction=0;
		firstWheel->CreateFixture(&fixtureDef);
		firstWheel->CreateFixture(&shape, 2.0f);
		//! revolute joint between second wheel and invisible body                
                rjd.Initialize(fakeBody, secondWheel, b2Vec2(-4.0f, 5.0f));
                rjd.motorSpeed = -1.0 * b2_pi;
                rjd.maxMotorTorque = 1000000000.0f;
                rjd.enableMotor = true;
                mj=(b2RevoluteJoint *)m_world->CreateJoint(&rjd);
		//! revolute joint between first wheel and invisible body
                rjd.Initialize(fakeBody, firstWheel, b2Vec2(-34.0f, 5.0f));
		mj2=(b2RevoluteJoint *)m_world->CreateJoint(&rjd);
		rjd.enableMotor = false;
		//! rod connecting the two wheels
                shape.SetAsBox(15.0f, 0.125f);
                bd.type = b2_dynamicBody;
                bd.position.Set(-15.0f, 5.0f);
                b2Body* rod_bw_two_wheels = m_world->CreateBody(&bd);
		fixtureDef.shape = &shape;
		fixtureDef.density=2;
		fixtureDef.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
		rod_bw_two_wheels->CreateFixture(&fixtureDef);
		//! revolute joint between second wheel and rod connecting two wheels
		rjd.Initialize(rod_bw_two_wheels, secondWheel, b2Vec2(0.0f, 5.0f));
                m_world->CreateJoint(&rjd);
		//! revolute joint between first wheel and rod connecting two wheels
		rjd.Initialize(rod_bw_two_wheels, firstWheel, b2Vec2(-30.0f, 5.0f));
                m_world->CreateJoint(&rjd);
		//! fake invisible body         
                fake.position.Set(0.0f, 25.0f);
                fakeBody = m_world->CreateBody(&fake);
                //! polygon with six vertices
                float32 a=0.0f,b=0.0f;
                b2Vec2 polyWithSixVert[6];
                polyWithSixVert[0].Set(a, b);
                polyWithSixVert[1].Set(a-1.0f, b-2.0f);
                polyWithSixVert[2].Set(a, b-4.0f);
                polyWithSixVert[3].Set(a+1.0f, b-4.0f);
                polyWithSixVert[4].Set(a+2.0f, b-2.0f);
                polyWithSixVert[5].Set(a+1.0f, b);
                b2PolygonShape sixVertPoly;
                sixVertPoly.Set(polyWithSixVert, 6);
                bd.type = b2_staticBody;
                bd.position.Set(0.0f, 25.0f);
                b2Body* polygon_with_6_vertices = m_world->CreateBody(&bd);
                fixtureDef.density=2.0f;
                fixtureDef.shape = &sixVertPoly;
                polygon_with_6_vertices->CreateFixture(&fixtureDef);
		//! revolute joint between fake body and polygon with 6 vertices
                b2RevoluteJointDef rjd;
                rjd.Initialize(fakeBody, polygon_with_6_vertices, b2Vec2(0.0f, 25.0f));
                m_world->CreateJoint(&rjd);
                //! rod from 6 sided polygon
                shape.SetAsBox(4.375f, 0.25f);
                bd.type = b2_dynamicBody;
                bd.position.Set(3.2f, 18.4f);
                bd.angle=-1;
                b2Body* rod_from_topPoly = m_world->CreateBody(&bd);
		fixtureDef.shape = &shape;
		fixtureDef.density=2.0f;
		fixtureDef.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
		rod_from_topPoly->CreateFixture(&fixtureDef);
		//! revolute joint between top polygon with 6 vertices and rod hanging from it
                rjd.Initialize(rod_from_topPoly, polygon_with_6_vertices, b2Vec2(0.8f, 21.5f));
		rjd.upperAngle = 0.25f * b2_pi;rjd.lowerAngle = -0.15f * b2_pi;
		rjd.enableLimit=true;
		rjd.enableMotor=true;
                m_world->CreateJoint(&rjd);
		rjd.enableMotor=false;
		rjd.enableLimit=false;
		//! rod between top circle and rod from 6 sided polygon
                shape.SetAsBox(8.175f, 0.25f);
                bd.position.Set(13.8f, 15.0f);
                bd.angle=0.0;
                b2Body* rod_bw_rodFrom6sidedPoly_topCircle = m_world->CreateBody(&bd);
		fixtureDef.shape = &shape;
		rod_bw_rodFrom6sidedPoly_topCircle->CreateFixture(&fixtureDef);fixtureDef.filter.groupIndex = -9;
		bd.angle=0;
		//! revolute joint between rod from 6 sided polygon and rod from it to top circle
                rjd.Initialize(rod_bw_rodFrom6sidedPoly_topCircle, rod_from_topPoly, b2Vec2(5.0f, 15.0f));
                m_world->CreateJoint(&rjd);             
                //! square piston               
                shape.SetAsBox(1.5f, 1.5f);		
                bd.type = b2_dynamicBody;
                bd.position.Set(19.0f, 5.0f);
                b2Body* squarePiston = m_world->CreateBody(&bd);
		//b2FixtureDef fixtureDef1;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.filter.categoryBits = 0x0002; //! to avoid overlapping bodies from colliding
		squarePiston->CreateFixture(&fixtureDef);                
		//! diamond below square piston
                b2Vec2 vertices[4];
                vertices[0].Set(0.0f, 0.0f);
                vertices[1].Set(-1.25f, -2.5f);
                vertices[2].Set(0.0f, -5.0f);
                vertices[3].Set(1.25f, -2.5f);
                int32 count = 4;
                b2PolygonShape polygon;
                polygon.Set(vertices, count);
		b2FixtureDef fixtureDef2;
		fixtureDef2.shape = &polygon;
		fixtureDef2.filter.categoryBits = 0x0001; //! to avoid overlapping bodies from colliding
		squarePiston->CreateFixture(&fixtureDef2);
                //! circle on bounder
                shape1.m_radius = 0.5f;
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(27.0f, 3.0f);
                b2Body* circle_on_bounder = m_world->CreateBody(&bd);
                fixtureDef.shape = &shape1;
                fixtureDef.filter.categoryBits = 0x0001; //! to avoid overlapping bodies from colliding
                circle_on_bounder->CreateFixture(&fixtureDef);
                //! rod connecting circle to diamond
                shape.SetAsBox(3.1f, 0.25f);
                bd.type = b2_dynamicBody;
                bd.position.Set(22.0f, 1.4f);
                bd.angle=0.42f;
                b2Body* rod_bw_circle_diamond = m_world->CreateBody(&bd);
                b2FixtureDef fixtureDe;
                fixtureDe.shape = &shape;
                rod_bw_circle_diamond->CreateFixture(&fixtureDe);
		//! revolute joint between square piston and rod connecting bearing to diamond
                rjd.Initialize(rod_bw_circle_diamond, squarePiston, b2Vec2(19.0f, 0.0f));
                m_world->CreateJoint(&rjd);
		//! revolute joint between circle on bounder and rod connecting bearing to diamond
                rjd.Initialize(rod_bw_circle_diamond, circle_on_bounder, b2Vec2(25.0f, 3.0f));
                m_world->CreateJoint(&rjd);
                //! circle on top
                b2CircleShape shape1;
		shape1.m_p.Set(-5.6f, 0.0f);
                shape1.m_radius = 0.5f;
                bd.type = b2_dynamicBody;
                fixtureDe.shape = &shape1;
		//! rod between top and bottom circle
                shape.SetAsBox(5.6f, 0.25f);
                bd.type = b2_dynamicBody;
                bd.position.Set(23.75f, 9.0f);
                bd.angle=-1.33f;
                b2Body* rod_bw_two_circles = m_world->CreateBody(&bd);
		bd.angle=0;
                fixtureDef.shape = &shape;
                fixtureDef.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
                rod_bw_two_circles->CreateFixture(&fixtureDef);
		rod_bw_two_circles->CreateFixture(&fixtureDe);
		//! revolute joint between circle on bounder and rod between the two circles
                rjd.Initialize(rod_bw_two_circles, circle_on_bounder, b2Vec2(25.0f, 3.0f));
                m_world->CreateJoint(&rjd);
                //! rod connecting large rectangular piston to rod connecting two circles
                shape.SetAsBox(4.3f, 0.125f);
                bd.type = b2_dynamicBody;
                bd.position.Set(28.2f, 9.7f);
                b2Body* rodRectPiston = m_world->CreateBody(&bd);
                rodRectPiston->CreateFixture(&shape, 0.2f);     
                //! the thin rectangular bodies in which the bearings/ circles are bound have been called bounder           
                //! bounder 1
                shape.SetAsBox(8.5f, 0.5f);
                bd.type = b2_staticBody;
                bd.position.Set(17.0f, 3.1f);
                b2Body* bounder1 = m_world->CreateBody(&bd);                
                fixtureDef.shape = &shape;
                fixtureDef.density = 1.0f;
                fixtureDef.filter.categoryBits = 0x0002; //! to avoid overlapping bodies from colliding
                fixtureDef.filter.maskBits = 0x0002;
                bounder1->CreateFixture(&fixtureDef);
                //! bounder 2
                bd.position.Set(17.0f, 7.1f);
                b2Body* bounder2 = m_world->CreateBody(&bd);
                bounder2->CreateFixture(&fixtureDef);
                //! bounder 3
                bd.position.Set(35.0f, 7.8f);
                b2Body* bounder3 = m_world->CreateBody(&bd);
                bounder3->CreateFixture(&shape, 2.0f);
                //! bounder 4
                bd.position.Set(35.0f, 2.0f);
                b2Body* bounder4 = m_world->CreateBody(&bd);
                bounder4->CreateFixture(&shape, 2.0f);
                //! bounder 5
                bd.position.Set(35.0f, 12.1f);
                b2Body* bounder5 = m_world->CreateBody(&bd);
                bounder5->CreateFixture(&shape, 2.0f);
		//! bounder 6
                shape.SetAsBox(8.5f, 0.5f);
                bd.type = b2_staticBody;
                bd.position.Set(22.5f, 13.5f);
                b2Body* bounder6 = m_world->CreateBody(&bd);                
                f.shape = &shape;
                f.density = 1.0f;
                f.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
                bounder6->CreateFixture(&f);
		//! bounder 7
                shape.SetAsBox(8.5f, 0.5f);
                bd.type = b2_staticBody;
                bd.position.Set(22.5f, 16.2f);
                b2Body* bounder7 = m_world->CreateBody(&bd);
                f.shape = &shape;
                f.density = 1.0f;
                f.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
                bounder7->CreateFixture(&f);
                //! rod connecting wheel to square piston
                shape.SetAsBox(8.675f, 0.125f);
                bd.type = b2_dynamicBody;
                bd.position.Set(8.75f, 5.0f);
                b2Body* rodWheel2Piston = m_world->CreateBody(&bd);
                rodWheel2Piston->CreateFixture(&shape, 2.0f);
                //! rod connecting square piston to thin rect piston
                shape.SetAsBox(7.5f, 0.125f);
                bd.type = b2_dynamicBody;
                bd.position.Set(28.0f, 5.0f);
                b2Body* rod_bw_sq_thin_piston = m_world->CreateBody(&bd);
                b2FixtureDef fixtureDef23;
                fixtureDef23.shape = &shape;
                fixtureDef23.filter.groupIndex = -8; //! to avoid overlapping bodies from colliding
                rod_bw_sq_thin_piston->CreateFixture(&fixtureDef23);
                //! thin vertical rectangular piston
                shape.SetAsBox(0.8f, 2.5f);
                bd.type = b2_dynamicBody;
		bd.angle=0.2;
                bd.position.Set(36.0f, 5.0f);
                thinPiston = m_world->CreateBody(&bd);
                thinPiston->CreateFixture(&shape, 2.0f);
                //! large rectangular piston
                shape.SetAsBox(3.5f, 1.5f);
                bd.type = b2_dynamicBody;
                bd.position.Set(36.0f, 10.0f);
                b2Body* largePiston = m_world->CreateBody(&bd);
                largePiston->CreateFixture(&shape, 1.0f);		
		//! revolute joint between second wheel and rod connecting it to square piston             
                rjd.enableMotor=false;rjd.Initialize(secondWheel, rodWheel2Piston, b2Vec2(0.075f, 5.0f));
                m_world->CreateJoint(&rjd);
		//! revolute joint between square piston and rod connecting it to second wheel
                rjd.enableMotor=false;rjd.Initialize(squarePiston, rodWheel2Piston, b2Vec2(17.5f, 5.0f));
                m_world->CreateJoint(&rjd);
		//! revolute joint between square piston and rod connecting it to thin piston
                rjd.enableMotor=false;
		rjd.Initialize(squarePiston, rod_bw_sq_thin_piston, b2Vec2(20.5f, 5.0f));
                m_world->CreateJoint(&rjd);
		//! revolute joint between thin piston and rod connecting it to square piston
		rjd.enableMotor=false;
                rjd.Initialize(thinPiston, rod_bw_sq_thin_piston, b2Vec2(35.5f, 5.0f));
                m_world->CreateJoint(&rjd);
		//! revolute joint between circle on top and rod connecting it to the rod connecting rod from 6 sided polygon
		rjd.enableMotor=false;
		rjd.Initialize(rod_bw_rodFrom6sidedPoly_topCircle, rod_bw_two_circles, b2Vec2(22.5f, 15.0f));
                m_world->CreateJoint(&rjd);	
		//! revolute joint between large piston and rod connected to it
                rjd.Initialize(largePiston, rodRectPiston, largePiston->GetWorldCenter());
		m_world->CreateJoint(&rjd);
		//! revolute joint bw rod connecting two circles and rod connecting this rod to large rectangular piston
		rjd.Initialize(rod_bw_two_circles, rodRectPiston, b2Vec2(23.3f, 9.7f));
                m_world->CreateJoint(&rjd);

         
  }
  void dominos_t::keyboard(unsigned char key)
    {
        switch (key)
		{
		case 'd':
		mj->SetMotorSpeed(1.0 * b2_pi);
		mj2->SetMotorSpeed(1.0 * b2_pi);
		break;
		case 'a':
		mj->SetMotorSpeed(-1.0 * b2_pi);
		mj2->SetMotorSpeed(-1.0 * b2_pi);
		break;
		
		}
    }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
