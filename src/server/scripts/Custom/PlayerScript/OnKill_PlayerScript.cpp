#include "ScriptPCH.h"

class on_kill : public PlayerScript
{
public:
	on_kill() : PlayerScript("on_kill") { }

	void OnPvPKill(Player * killer, Player * victim)
	{
		if (killer->GetGUID() == victim->GetGUID())
			return;

		if (victim->GetMoney() > 10000)
			killer->ModifyMoney(killer->GetMoney() + 10000);
		victim->ModifyMoney(victim->GetMoney() - 10000);
//		break;
			//		handler->SendSysMessage");
	}
};

void AddSC_on_kill()
{
	new on_kill;
}