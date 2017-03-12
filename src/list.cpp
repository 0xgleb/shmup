#include "../include/list.hpp"
#include "../include/vector.hpp"

void doDamage(List<Ship>& enemies, List<Body>& bullets) {
	struct node<Ship> *current;
	for(current = enemies._first; current; current = (current) ? current->next : NULL) {
		current->val->applyDamage(20 * bullets.countIntersections(current->val->coord(), 
					enemies._selection->w, enemies._selection->h));
		if(current->val->health() <= 0) {
			current = enemies.delNode(current);
			enemies.addNode(new Ship((constant::window::width - constant::enemy::selW) / 3,
					constant::enemy::selH, constant::enemy::selX, constant::enemy::selY, 
					constant::enemy::selW, constant::enemy::selH));
			enemies.addNode(new Ship(2 * (constant::window::width - constant::enemy::selW) / 3,
					constant::enemy::selH, constant::enemy::selX, constant::enemy::selY, 
					constant::enemy::selW, constant::enemy::selH));
		}
	}
}

Ship* findIntersections(List<Ship>& enemies, struct node<Ship> *target) {
	Vector tmp;
	struct node<Ship> *current = enemies._first;
	for(; current; current = (current) ? current->next : NULL) {
		if(current == target)
			continue;
		tmp = (current->val->coord() - target->val->coord());
		if(abs(tmp.x()) < enemies.selection()->w && abs(tmp.y()) < enemies.selection()->h)
			return current->val;
	}

	return NULL;
}

void changeVelocity(List<Ship>& enemies, Ship& player) {
	Vector tmp;
	Ship *conf;
	for(struct node<Ship> *current = enemies._first; current; current = current->next) {
		tmp = player.coord() - current->val->coord();
		tmp = tmp / tmp.abs();
		current->val->velocity(tmp);
		if(conf = findIntersections(enemies, current)) {
			current->val->coord().x(conf->coord().x() - enemies.selection()->w);
			current->val->coord().y(conf->coord().y() - enemies.selection()->h);
			std::cout << "x: " << current->val->coord().x() << 
					", y: " << current->val->coord().y() << std::endl;
		}
	}
}
