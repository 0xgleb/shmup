#include "../include/list.hpp"

void getDamage(List<Ship>& enemies, List<Body>& bullets) {
	for(struct node<Ship> *current = enemies._first; current; current = current->next)
		current->val->getDamage(10 * bullets.countIntersections(current->val->coord(), 
					bullets._selection->w, bullets._selection->h));
}
