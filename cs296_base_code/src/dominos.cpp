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
	 b2Body* m_ball;
    b2RevoluteJoint* m_joint;
    b2RevoluteJoint* m_joint1;
    b2PrismaticJoint* m_joint2;
      
        b2Body* ground = NULL;
        {
            b2BodyDef bd;
            ground = m_world->CreateBody(&bd);
            b2EdgeShape shape;
            shape.Set(b2Vec2(-70.0f, -4.5f), b2Vec2(70.0f, -4.5f));
            b2FixtureDef fd;
            fd.shape = &shape;
            ground->CreateFixture(&fd);
        }



        {
            b2Body* prevBody = ground;

            //! define crank
            {
                b2PolygonShape shape;
                shape.SetAsBox(2.0f, 0.5f);
                b2CircleShape shape1;
                shape1.m_p.Set(-2.0f, 0.0f);
                shape1.m_radius = 9.5f;
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-2.0f, 5.0f);
                b2Body* body = m_world->CreateBody(&bd);

b2FixtureDef fixtureDef24;
fixtureDef24.shape = &shape;
fixtureDef24.filter.groupIndex = 9;
//b2Fixture* myFixture24 = body->CreateFixture(&fixtureDef24);
b2FixtureDef fixtureDef244;
fixtureDef244.shape = &shape1;
fixtureDef244.filter.groupIndex = -9;
b2Fixture* myFixture25 = body->CreateFixture(&fixtureDef244);
body->CreateFixture(&shape, 2.0f);
                //body->CreateFixture(&shape1, 2.0f);

                //! a fake invisible object to support a revolute joint
                b2BodyDef fake;
                fake.position.Set(-4.0f, 5.0f);
                b2Body* bodyf = m_world->CreateBody(&fake);

                bd.position.Set(-32.0f, 5.0f);
                b2Body* bodyy = m_world->CreateBody(&bd);
                bodyy->CreateFixture(&shape, 2.0f);


fixtureDef244.shape = &shape1;
fixtureDef244.filter.groupIndex = -9;
bodyy->CreateFixture(&fixtureDef244);


                b2RevoluteJointDef rjd;
                rjd.Initialize(bodyf, body, b2Vec2(-4.0f, 5.0f));
                rjd.motorSpeed = -1.0f * b2_pi;
                rjd.maxMotorTorque = 10000.0f;
                rjd.enableMotor = true;
                m_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);

                rjd.Initialize(bodyf, bodyy, b2Vec2(-34.0f, 5.0f));

b2RevoluteJoint* m_jointt1 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);


                shape.SetAsBox(15.0f, 0.125f);
                bd.type = b2_dynamicBody;
                bd.position.Set(-15.0f, 5.0f);
                b2Body* thinn = m_world->CreateBody(&bd);

fixtureDef244.shape = &shape;
fixtureDef244.density=2;
fixtureDef244.filter.groupIndex = -9;
thinn->CreateFixture(&fixtureDef244);

            //  thinn->CreateFixture(&shape, 2.0f);

rjd.Initialize(thinn, body, b2Vec2(0.0f, 5.0f));
                 (b2RevoluteJoint*)m_world->CreateJoint(&rjd);
rjd.Initialize(thinn, bodyy, b2Vec2(-30.0f, 5.0f));
                 (b2RevoluteJoint*)m_world->CreateJoint(&rjd);


                prevBody = body;
            }


            {
                b2BodyDef fake;
                fake.position.Set(0.0f, 25.0f);
                b2Body* bodyf = m_world->CreateBody(&fake);
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
                b2BodyDef bdd;
                bdd.type = b2_staticBody;
                bdd.position.Set(0.0f, 25.0f);
                b2Body* polygon_with_6_vertices = m_world->CreateBody(&bdd);
                b2FixtureDef fixtureDef2d;
                fixtureDef2d.density=2.0f;
                fixtureDef2d.shape = &sixVertPoly;
                polygon_with_6_vertices->CreateFixture(&fixtureDef2d);

                b2RevoluteJointDef rjd3;
                rjd3.Initialize(bodyf, polygon_with_6_vertices, b2Vec2(0.0f, 25.0f));
                //rjd3.motorSpeed = -1.0f * b2_pi;
                //rjd3.maxMotorTorque = 10000.0f;
                //rjd3.enableMotor = true;
                m_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&rjd3);


                //Two rods
                b2PolygonShape s;
                s.SetAsBox(4.675f, 0.25f);
                b2BodyDef bg;
                bg.type = b2_dynamicBody;
                bg.position.Set(3.2f, 18.0f);
                bg.angle=-1;
                b2Body* rod4 = m_world->CreateBody(&bg);

b2FixtureDef fixtureDef245;
fixtureDef245.shape = &s;
fixtureDef245.density=2.0f;
fixtureDef245.filter.groupIndex = -9;
rod4->CreateFixture(&fixtureDef245);
//rod4->CreateFixture(&s, 2.0f);
                rjd3.Initialize(rod4, polygon_with_6_vertices, b2Vec2(0.8f, 21.5f));
                rjd3.enableMotor = false;
                m_world->CreateJoint(&rjd3);


                s.SetAsBox(8.675f, 0.25f);
                bg.position.Set(14.2f, 15.0f);
                bg.angle=0.08;
                b2Body* rod5 =m_world->CreateBody(&bg);
fixtureDef245.shape = &s;
//fixtureDef245.filter.groupIndex = 3;
rod5->CreateFixture(&fixtureDef245);
//rod5->CreateFixture(&s, 2.0f);
                rjd3.Initialize(rod5, rod4, b2Vec2(6.0f, 14.0f));
                m_world->CreateJoint(&rjd3);
                //rjd3.Initialize(rod5, bodyc, b2Vec2(22.5f, 15.0f));
                //m_world->CreateJoint(&rjd3);


                //square piston
                b2PolygonShape shape;
                shape.SetAsBox(1.5f, 1.5f);
                //poly below square piston
                b2Vec2 vertices[4];
                vertices[0].Set(0.0f, 0.0f);
                vertices[1].Set(-1.25f, -2.5f);
                vertices[2].Set(0.0f, -5.0f);
                vertices[3].Set(1.25f, -2.5f);
                int32 count = 4;
                b2PolygonShape polygon;
                polygon.Set(vertices, count);

                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(19.0f, 5.0f);
                b2Body* box = m_world->CreateBody(&bd);


b2FixtureDef fixtureDef1;
fixtureDef1.shape = &shape;
fixtureDef1.density = 1.0f;
fixtureDef1.filter.categoryBits = 0x0002;
//fixtureDef1.filter.maskBits = 0x0002;
b2Fixture* myFixture1 = box->CreateFixture(&fixtureDef1);
b2FixtureDef fixtureDef2;
fixtureDef2.shape = &polygon;
fixtureDef2.filter.categoryBits = 0x0001;
//fixtureDef2.filter.maskBits = 0x0001;
b2Fixture* myFixture2 = box->CreateFixture(&fixtureDef2);
                //! circle on top
                b2CircleShape shape1;
                shape1.m_radius = 0.5f;
                b2BodyDef bd1;
                bd1.type = b2_dynamicBody;
                bd1.position.Set(25.0f, 3.0f);
                b2Body* circle_on_top = m_world->CreateBody(&bd1);
                b2FixtureDef fixtureDef3;
                fixtureDef3.shape = &shape1;
                fixtureDef3.filter.categoryBits = 0x0001;
                circle_on_top->CreateFixture(&fixtureDef3);
                //! rod connecting circle to diamond
                b2BodyDef bdc;
                shape.SetAsBox(3.1f, 0.25f);
                bdc.type = b2_dynamicBody;
                bdc.position.Set(22.0f, 1.4f);
                bdc.angle=0.42f;
                b2Body* rod_bw_circle_diamond = m_world->CreateBody(&bdc);
                b2FixtureDef fixtureDe;
                fixtureDe.shape = &shape;
                b2Fixture* myFixturen = rod_bw_circle_diamond->CreateFixture(&fixtureDe);



                b2RevoluteJointDef rjd1;
                rjd1.Initialize(rod_bw_circle_diamond, box, b2Vec2(19.0f, 0.0f));
                m_world->CreateJoint(&rjd1);
                rjd1.Initialize(rod_bw_circle_diamond, circle_on_top, b2Vec2(25.0f, 3.0f));
                m_world->CreateJoint(&rjd1);
                //top small circle with prismatic joint
                b2CircleShape shapec;
                shapec.m_radius = 0.5f;
                b2BodyDef bde;
                bde.type = b2_dynamicBody;
                bde.position.Set(22.5f, 15.0f);
                b2Body* bodyc = m_world->CreateBody(&bde);
                b2FixtureDef fixtureDefc;
                fixtureDefc.shape = &shapec;
                b2Fixture* myFixturec = bodyc->CreateFixture(&fixtureDefc);
                //! rod between top and bottom circle
                shape.SetAsBox(5.6f, 0.25f);
                bdc.type = b2_dynamicBody;
                bdc.position.Set(23.75f, 9.0f);
                bdc.angle=-1.33f;
                b2Body* rod_bw_two_circles = m_world->CreateBody(&bdc);
                b2FixtureDef fixtureDe2;
                fixtureDe2.shape = &shape;
                fixtureDe2.filter.groupIndex = -8;
                rod_bw_two_circles->CreateFixture(&fixtureDe2);

                rjd1.Initialize(rod_bw_two_circles, circle_on_top, b2Vec2(25.0f, 3.0f));
                m_world->CreateJoint(&rjd1);





                //! rod connecting large rectangular piston to rod connecting two circles
                shape.SetAsBox(4.3f, 0.125f);
                bd.type = b2_dynamicBody;
                bd.position.Set(28.2f, 10.0f);
                b2Body* rodRectPiston = m_world->CreateBody(&bd);
                rodRectPiston->CreateFixture(&shape, 0.2f);
                //! revolute joint bw rod connecting two circles and rod connecting this rod to large rectangular piston
                rjd1.Initialize(rod_bw_two_circles, rodRectPiston, b2Vec2(23.9f, 10.0f));
                m_world->CreateJoint(&rjd1);
                //! bounder 1
                shape.SetAsBox(8.5f, 0.5f);
                bd.type = b2_staticBody;
                bd.position.Set(17.0f, 3.0f);
                b2Body* bounder1 = m_world->CreateBody(&bd);
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &shape;
                fixtureDef.density = 1.0f;
                fixtureDef.filter.categoryBits = 0x0002;
                fixtureDef.filter.maskBits = 0x0002;
                bounder1->CreateFixture(&fixtureDef);
                //! bounder 2
                bd.position.Set(17.0f, 7.1f);
                b2Body* bounder2 = m_world->CreateBody(&bd);
                bounder2->CreateFixture(&fixtureDef);
                //! bounder 3
                bd.position.Set(35.0f, 8.0f);
                b2Body* bounder3 = m_world->CreateBody(&bd);
                bounder3->CreateFixture(&shape, 2.0f);
                //! bounder 4
                bd.position.Set(35.0f, 2.0f);
                b2Body* bounder4 = m_world->CreateBody(&bd);
                bounder4->CreateFixture(&shape, 2.0f);
                //! bounder 5
                bd.position.Set(35.0f, 12.0f);
                b2Body* bounder5 = m_world->CreateBody(&bd);
                bounder5->CreateFixture(&shape, 2.0f);
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
                fixtureDef23.filter.groupIndex = -8;
                rod_bw_sq_thin_piston->CreateFixture(&fixtureDef23);


                //! Thin vertical rectangular piston
                shape.SetAsBox(0.5f, 2.5f);
                bd.type = b2_dynamicBody;
                bd.position.Set(36.0f, 5.0f);
                b2Body* thinPiston = m_world->CreateBody(&bd);
                thinPiston->CreateFixture(&shape, 2.0f);
                //! Large rectangular piston
                shape.SetAsBox(3.5f, 1.5f);
                bd.type = b2_dynamicBody;
                bd.position.Set(36.0f, 10.0f);
                b2Body* largePiston = m_world->CreateBody(&bd);
                largePiston->CreateFixture(&shape, 0.001f);

                rjd1.Initialize(largePiston, rodRectPiston, b2Vec2(32.5f, 10.0f));
                m_world->CreateJoint(&rjd1);


                b2RevoluteJointDef rjd;
                rjd.Initialize(prevBody, rodWheel2Piston, b2Vec2(0.075f, 5.0f));
                rjd.enableMotor = false;
                m_world->CreateJoint(&rjd);
                rjd.Initialize(box, rodWheel2Piston, b2Vec2(17.5f, 5.0f));
                m_world->CreateJoint(&rjd);
                rjd.Initialize(box, rod_bw_sq_thin_piston, b2Vec2(20.5f, 5.0f));
                m_world->CreateJoint(&rjd);
                rjd.Initialize(thinPiston, rod_bw_sq_thin_piston, b2Vec2(35.5f, 5.0f));
                m_world->CreateJoint(&rjd);

                rjd1.Initialize(rod5, bodyc, b2Vec2(21.5f, 15.4f));
                m_world->CreateJoint(&rjd1);
                rjd1.Initialize(rod_bw_two_circles, bodyc, b2Vec2(22.0f, 15.0f));
                m_world->CreateJoint(&rjd1);

            }
        

    
}

         
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
