#include "misc.h"
#include "bug_on.h"

struct rcu_head;

void wakeme_after_rcu(struct rcu_head *head)
{
	BUG();
}
