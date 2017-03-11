#include "../include/list.hpp"

void doDamage(List<Ship>& enemies, List<Body>& bullets) {
	for(struct node<Ship> *current = enemies._first; current; current = current->next)
		current->val->applyDamage(10 * bullets.countIntersections(current->val->coord(), 
					enemies._selection->w, enemies._selection->h));
}
