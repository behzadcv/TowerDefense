#include "monster.hh"

Monster::Monster(std::pair<int, int> tile_position, path_type type, float frametime) : Object(tile_position){
	if(type == path_type::horizontal)	{
		dir = direction::right;
		lastdir = direction::right;
	}
	else	{
		dir = direction::down;
		lastdir = direction::down;
	}
	obtype = ObjectType::Monst;
	last_moved = 0;
	distance_traveled = 0;
	freeze_time = 0;
	slowed = 0;
	slowed_until = 0;
	slowed_until_extended = false;
	lastframe = frametime;
	reversed = false;
	reversed_until = 0;
	scoreOnDeath = 0.0;
	moneyOnDeath = 0.0;
}

//required for infinity mode
/*Monster::Monster(std::pair<int, int> &tile_position, path_type &type, float frametime, MoveType mt, float hp, float mhp, float sp, float sOD, float mOD) : Object(tile_position){
	if(type == path_type::horizontal)	{
		dir = direction::right;
		lastdir = direction::right;
	}
	else	{
		dir = direction::down;
		lastdir = direction::down;
	}
	obtype = ObjectType::Monst;
	last_moved = 0;
	distance_traveled = 0;
	freeze_time = 0;
	slowed = 0;
	slowed_until = 0;
	slowed_until_extended = false;
	lastframe = frametime;
	reversed = false;
	reversed_until = 0;
	scoreOnDeath = sOD;
	moneyOnDeath = mOD;
	health = hp;
	maxhealth = mhp;
	speed = sp;
	max_speed = sp;
	mtype = mt;
}*/

MoveType Monster::getMoveType() const	{
	return mtype;
}

float Monster::getHealth() const	{
	return health;
}

float Monster::getMaxHealth() const	{
	return maxhealth;
}

float Monster::getSpeed() const	{
	return speed;
}

void Monster::paused(float frametime)	{
	lastframe = frametime;
}

void Monster::reverse()	{
	//std::cout << "reversing" << std::endl;
	if(dir == direction::right)
		dir = direction::left;
	else if(dir == direction::left)
		dir = direction::right;
	else if(dir == direction::up)
		dir = direction::down;
	else if(dir == direction::down)
		dir = direction::up;
}

float Monster::getDistanceTraveled() const	{
	return distance_traveled;
}

void Monster::update(float frametime, tdMap &map)	{
	//std::cout << getSpeed() << std::endl;
	//draw the monster
	sf::Vector2i fordrawing;
	fordrawing.x = (int)(center_position.x - 42.5 + 0.5);		//converts float position to int for drawing purposes
	fordrawing.y = (int)(center_position.y - 42.5 + 0.5);
	if(frametime < slowed_until)	{
		speed = max_speed - slowed*max_speed;
	}
	else	{
		speed = max_speed;
		slowed = 0;
		slowed_until = 0;
	}
	float prev_speed =  getSpeed();
	if(frametime - last_moved < freeze_time)	{		//checks if monster is frozen
		speed = 0;
		if(dir == direction::left)
			draw(fordrawing, 0.0, -1, getHealth()/getMaxHealth() * 100);
		else
			draw(fordrawing, 0.0, 1, getHealth()/getMaxHealth() * 100);
		/*if(slowed && slowed_until_extended == false)	{					//if the monster was slowed, slowing continues after it melts
			slowed_until += 4;
			slowed_until_extended = true;
		}*/
	}
	else	{
		speed = prev_speed;
		freeze_time = 0;
		slowed_until_extended = false;
		if(((frametime > reversed_until) && reversed) || (reversed && distance_traveled < 2))	{
			reverse();
			reversed = false;
			reversed_until = 0;
		}
		move(frametime - lastframe, map);
		last_moved = frametime;
	}
	lastframe = frametime;
}

void Monster::move(float dt, tdMap &map)	{
	//draw the monster
	sf::Vector2i fordrawing;
	fordrawing.x = (int)(center_position.x - 42.5 + 0.5);		//converts float position to int for drawing purposes
	fordrawing.y = (int)(center_position.y - 42.5 + 0.5);

	std::pair<int, int> currentTile;
	sf::Vector2i tile_center;
	std::pair<terrain, path_type> temp;

	if(distance_traveled == 0)	{
		currentTile = getTilePosition();
	}
	else	{
		currentTile.first = (center_position.x)/85;
		currentTile.second = (center_position.y - 40)/85;
	}

	tile_center.x = currentTile.first*85 + 42.5;
	tile_center.y = currentTile.second*85 + 82.5;
	temp = map.getTileTypes(currentTile.first, currentTile.second);

	if(getTilePosition() == currentTile)	{
		dir = direction::right;
	}
//Which way to draw monster
	if(dir == direction::right)
		draw(fordrawing, speed/350.0, 1, getHealth()/getMaxHealth() * 100);
	else if(dir == direction::left)
		draw(fordrawing, speed/350.0, -1, getHealth()/getMaxHealth() * 100);
	else if(dir == direction::down)
		//if(lastdir == direction::right)
			draw(fordrawing, speed/350.0, 1, getHealth()/getMaxHealth() * 100);
		//else
		//	thisUI.drawAtPositionDirection(fordrawing, speed/350.0, -1);
	else if(dir == direction::up)
		//if(lastdir == direction::right)
			draw(fordrawing, speed/350.0, 1, getHealth()/getMaxHealth() * 100);
		//else
		//	thisUI.drawAtPositionDirection(fordrawing, speed/350.0, -1);
//direction RIGHT
	if(dir == direction::right && temp.second == path_type::horizontal)	{
		center_position.x += speed*dt;
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
	}

	else if(dir == direction::right && temp.second == path_type::leftToDown)	{
		if((center_position.x + speed*dt) < tile_center.x)	{
			center_position.x += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.x - center_position.x);
			else
				distance_traveled += (tile_center.x - center_position.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			dir = direction::down;
		}
	}

	else if (dir == direction::right && temp.second == path_type::leftToTop)	{
		if((center_position.x + speed*dt) < tile_center.x)	{
			center_position.x += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.x - center_position.x);
			else
				distance_traveled += (tile_center.x - center_position.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			dir = direction::up;
		}
	}

	else if (dir == direction::right && temp.second == path_type::rightToTop)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.x  += speed*dt;
	}

	else if (dir == direction::right && temp.second == path_type::rightToDown)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.x  += speed*dt;
	}

	else if (dir == direction::right && temp.second == path_type::leftUpDown)	{
		if((center_position.x + speed*dt) < tile_center.x)	{
			center_position.x += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.x - center_position.x);
			else
				distance_traveled += (tile_center.x - center_position.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y -=1;
				dir = direction::up;
			}
			else	{
				dir = direction::down;
				center_position.y +=1;
			}
		}
	}

	else if (dir == direction::right && temp.second == path_type::leftRightUp)	{
		if((center_position.x + speed*dt) < tile_center.x)	{
			center_position.x += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.x > tile_center.x)	{
			center_position.x += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.x - center_position.x);
			else
				distance_traveled += (tile_center.x - center_position.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.x +=1;
				dir = direction::right;
			}
			else	{
				dir = direction::up;
				center_position.y -=1;
			}
		}
	}

	else if (dir == direction::right && temp.second == path_type::leftRightDown)	{
		if(center_position.x < tile_center.x && (center_position.x + speed*dt) < tile_center.x)	{
			center_position.x += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.x > tile_center.x)	{
			center_position.x += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.x - center_position.x);
			else
				distance_traveled += (tile_center.x - center_position.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.x +=1;
				dir = direction::right;
			}
			else	{
				dir = direction::down;
				center_position.y +=1;
			}
		}
	}

	else if (dir == direction::right && temp.second == path_type::rightUpDown)	{
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
		center_position.x  += speed*dt;
	}

//direction LEFT
	else if(dir == direction::left && temp.second == path_type::horizontal)	{
		center_position.x -= speed*dt;
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
	}

	else if(dir == direction::left && temp.second == path_type::rightToDown)	{
		if((center_position.x - speed*dt) > tile_center.x)	{
			center_position.x -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.x - tile_center.x);
			else
				distance_traveled += (center_position.x - tile_center.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			dir = direction::down;
		}
	}

	else if (dir == direction::left && temp.second == path_type::rightToTop)	{
		if((center_position.x - speed*dt) > tile_center.x)	{
			center_position.x -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.x - tile_center.x);
			else
				distance_traveled += (center_position.x - tile_center.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			dir = direction::up;
		}
	}


	else if (dir == direction::left && temp.second == path_type::leftToTop)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.x  -= speed*dt;
	}


	else if (dir == direction::left && temp.second == path_type::leftToDown)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.x  -= speed*dt;
	}

	else if(dir == direction::left && temp.second == path_type::leftUpDown)	{
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
		center_position.x  -= speed*dt;
	}

	else if (dir == direction::left && temp.second == path_type::leftRightUp)	{
		if((center_position.x - speed*dt) > tile_center.x)	{
			center_position.x -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.x < tile_center.x)	{
			center_position.x -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.x - tile_center.x);
			else
				distance_traveled += (center_position.x - tile_center.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y -=1;
				dir = direction::up;
			}
			else	{
				dir = direction::left;
				center_position.x -=1;
			}
		}
	}

	else if (dir == direction::left && temp.second == path_type::leftRightDown)	{
		if((center_position.x - speed*dt) > tile_center.x)	{
			center_position.x -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.x < tile_center.x)	{
			center_position.x -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.x - tile_center.x);
			else
				distance_traveled += (center_position.x - tile_center.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y +=1;
				dir = direction::down;
			}
			else	{
				dir = direction::left;
				center_position.x -=1;
			}
		}
	}

	else if (dir == direction::left && temp.second == path_type::rightUpDown)	{
		if((center_position.x - speed*dt) > tile_center.x)	{
			center_position.x -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.x - tile_center.x);
			else
				distance_traveled += (center_position.x - tile_center.x);
			center_position.x  = tile_center.x;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y -=1;
				dir = direction::up;
			}
			else	{
				dir = direction::down;
				center_position.y +=1;
			}
		}
	}

//direction UP
	else if(dir == direction::up && temp.second == path_type::vertical)	{
		center_position.y -= speed*dt;
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
	}

	else if(dir == direction::up && temp.second == path_type::leftToDown)	{
		if((center_position.y - speed*dt) > tile_center.y)	{
			center_position.y -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.y - tile_center.y);
			else
				distance_traveled += (center_position.y - tile_center.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			dir = direction::left;
		}
	}

	else if (dir == direction::up && temp.second == path_type::rightToDown)	{
		if((center_position.y - speed*dt) > tile_center.y)	{
			center_position.y -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.y - tile_center.y);
			else
				distance_traveled += (center_position.y - tile_center.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			dir = direction::right;
		}
	}


	else if (dir == direction::up && temp.second == path_type::leftToTop)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.y  -= speed*dt;
	}


	else if (dir == direction::up && temp.second == path_type::rightToTop)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.y  -= speed*dt;
	}

	else if(dir == direction::up && temp.second == path_type::leftUpDown)	{
		if((center_position.y - speed*dt) > tile_center.y)	{
			center_position.y -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.y < tile_center.y)	{
			center_position.y -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.y - tile_center.y);
			else
				distance_traveled += (center_position.y - tile_center.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y -=1;
				dir = direction::up;
			}
			else	{
				dir = direction::left;
				center_position.x -=1;
			}
		}
	}

	else if(dir == direction::up && temp.second == path_type::leftRightUp)	{
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
		center_position.y  -= speed*dt;
	}

	else if(dir == direction::up && temp.second == path_type::rightUpDown)	{
		if((center_position.y - speed*dt) > tile_center.y)	{
			center_position.y -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.y < tile_center.y)	{
			center_position.y -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.y - tile_center.y);
			else
				distance_traveled += (center_position.y - tile_center.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y -=1;
				dir = direction::up;
			}
			else	{
				dir = direction::right;
				center_position.x +=1;
			}
		}
	}

	else if(dir == direction::up && temp.second == path_type::leftRightDown)	{
		if((center_position.y - speed*dt) > tile_center.y)	{
			center_position.y -= speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (center_position.y - tile_center.y);
			else
				distance_traveled += (center_position.y - tile_center.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.x -=1;
				dir = direction::left;
			}
			else	{
				dir = direction::right;
				center_position.x +=1;
			}
		}
	}

//direction DOWN
	else if(dir == direction::down && temp.second == path_type::vertical)	{
		center_position.y += speed*dt;
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
	}

	else if(dir == direction::down && temp.second == path_type::rightToTop)	{
		if((center_position.y + speed*dt) < tile_center.y)	{
			center_position.y += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.y - center_position.y);
			else
				distance_traveled += (tile_center.y - center_position.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			dir = direction::right;
		}
	}

	else if (dir == direction::down && temp.second == path_type::leftToTop)	{
		if((center_position.y + speed*dt) < tile_center.y)	{
			center_position.y += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.y - center_position.y);
			else
				distance_traveled += (tile_center.y - center_position.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			dir = direction::left;
		}
	}


	else if (dir == direction::down && temp.second == path_type::leftToDown)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.y  += speed*dt;
	}


	else if (dir == direction::down && temp.second == path_type::rightToDown)	{
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
			center_position.y  += speed*dt;
	}

	else if(dir == direction::down && temp.second == path_type::leftUpDown)	{
		if((center_position.y + speed*dt) < tile_center.y)	{
			center_position.y += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.y > tile_center.y)	{
			center_position.y += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.y - center_position.y);
			else
				distance_traveled += (tile_center.y - center_position.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y +=1;
				dir = direction::down;
			}
			else	{
				dir = direction::left;
				center_position.x -=1;
			}
		}
	}

	else if(dir == direction::down && temp.second == path_type::leftRightUp)	{
		if((center_position.y + speed*dt) < tile_center.y)	{
			center_position.y += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else	{
			if(reversed)
				distance_traveled -= (tile_center.y - center_position.y);
			else
				distance_traveled += (tile_center.y - center_position.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.x +=1;
				dir = direction::right;
			}
			else	{
				dir = direction::left;
				center_position.x -=1;
			}
		}
	}

	else if(dir == direction::down && temp.second == path_type::rightUpDown)	{
		if((center_position.y + speed*dt) < tile_center.y)	{
			center_position.y += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}

		else if (center_position.y > tile_center.y)	{
			center_position.y += speed*dt;
			if(reversed)
				distance_traveled -= speed*dt;
			else
				distance_traveled += speed*dt;
		}


		else	{
			if(reversed)
				distance_traveled -= (tile_center.y - center_position.y);
			else
				distance_traveled += (tile_center.y - center_position.y);
			center_position.y  = tile_center.y;
			lastdir = dir;
			int number = rand() % 2;
			if(number == 0)	{
				center_position.y +=1;
				dir = direction::down;
			}
			else	{
				dir = direction::right;
				center_position.x +=1;
			}
		}
	}

	else if(dir == direction::down && temp.second == path_type::leftRightDown)	{
		if(reversed)
			distance_traveled -= speed*dt;
		else
			distance_traveled += speed*dt;
		center_position.y  += speed*dt;
	}
}

bool Monster::getShot(float time, float damage, float slowed1, float slowed_for, float freeze_for, float reverse_time1)	{
	bool killed = false;
	if(health > damage)	{
		health -= damage;
	}
	else
		return true;
	if(slowed1 > 0.0 && slowed_for && !getSlowImmunity())	{	//MAYBE THE MAGIC TOWERS CAN SLOW CUMULATIVELY!!	
		if(slowed1*slowed_for > slowed*(slowed_until - time))	{		//in case new slowing is better than old
			//if(slowed1 > max_speed)
			//	slowed = max_speed;
			//else
			slowed = slowed1;
			std::cout << slowed << std::endl;
			slowed_until = time + slowed_for;
		}
	}

	if(freeze_for)	{
		freeze_time += freeze_for;
	}

	if(reverse_time1)	{
		reversed_until = time + reverse_time1;
		if(!reversed)	{
			reverse();
			reversed = true;
		}
	}
	return killed;
}




