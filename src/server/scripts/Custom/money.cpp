class money: public CommandScript
{
public:
    money() : CommandScript("money") { }
 
    ChatCommand* GetCommands() const OVERRIDE
    {
        static ChatCommand commandTable[] =
        {
            { "money",    SEC_MODERATOR,  false, &HandleMoney,             "", NULL },
            { NULL,             0,                  false,  NULL,                            "", NULL }
        };
        return commandTable;
    }
 
    static bool HandleMoney(ChatHandler* handler, const char* /*args*/)
    {
	Player* player = handler->GetSession()->GetPlayer();
    	    if (!player)
            return false;
 
                Player* me = handler->GetSession()->GetPlayer();
                        return false;
						
				me->SetMoney(me->GetMoney() + 80000);
 
        return true;
    }
};
 
void AddSC_money()
{
    new money();
}