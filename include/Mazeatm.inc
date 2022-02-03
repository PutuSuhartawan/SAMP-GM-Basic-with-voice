new PlayerText:BankTextdraw_OP_0[6], PlayerText:BankTextdraw_OP_1[24], PlayerText:BankTextdraw_OP_2[12], PlayerText:BankTextdraw_OP_3[6];

#define BANKDEPOSIT 700
#define SETPLAYERID 701

enum @b_e
{
	bool:showed
}

new bankTextdraws[MAX_PLAYERS][@b_e];

/*public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) 
{
	if((newkeys & 65536) && (!IsPlayerInRangeOfPoint(playerid, 15.0, 1667.4260, -972.6691, 683.6873) || !IsPlayerInRangeOfPoint(playerid, 15.0, 2308.7346, -11.0134, 26.7422))) 
	{
		if(bankTextdraws[playerid][showed])
			return 1;

		bankTextdraws[playerid][showed] = true;
		SelectTextDraw(playerid, -1);
		showBankGUI_Page(playerid, 0);
	}
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) 
{
	if(playertextid == BankTextdraw_OP_0[5]) 
	{
		hideBankGUI_Page(playerid, 0), showBankGUI_Page(playerid, 1);

		new str[32];
		format(str, sizeof str, "Welcome~N~~G~~H~%s", GetPlayerNameEx(playerid));
		PlayerTextDrawSetString(playerid, BankTextdraw_OP_1[7], str);

		format(str, sizeof str, "~G~$%d", PlayerInfo[playerid][pBank]), PlayerTextDrawSetString(playerid, BankTextdraw_OP_1[9], str);
	}
	if(playertextid == BankTextdraw_OP_1[5]) 
	{
		bankTextdraws[playerid][showed] = false;
		hideBankGUI(playerid), CancelSelectTextDraw(playerid);
	}
	if(playertextid == BankTextdraw_OP_1[15])
	{
		PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[1], 1235677951), hideBankGUI_Page(playerid, 1), showBankGUI_Page(playerid, 2), SetPVarInt(playerid, "bankDepositValue", 0), PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[8], "~G~$0"), SetPVarInt(playerid, "typeDepositWithdraw", 1);
		PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[2], "DEPOSIT YOUR MONEY"), PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[7], "How much do you want to deposit"), PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[11], "Your Deposit"); 
	}
	if(playertextid == BankTextdraw_OP_2[3]) 
	{
		hideBankGUI_Page(playerid, 2), hideBankGUI_Page(playerid, 3), showBankGUI_Page(playerid, 1);
	}
	if(playertextid == BankTextdraw_OP_2[8] || playertextid == BankTextdraw_OP_3[2]) 
	{
		ShowPlayerDialog(playerid, BANKDEPOSIT, DIALOG_STYLE_INPUT, "Bank", "Set Value:", "Set", "Exit");
	}
	if(playertextid == BankTextdraw_OP_3[5]) 
	{
		ShowPlayerDialog(playerid, SETPLAYERID, DIALOG_STYLE_INPUT, "Bank", "Set Player ID:", "Set", "Exit");
	}
	if(playertextid == BankTextdraw_OP_2[9]) 
	{
		new amount = GetPVarInt(playerid, "bankDepositValue"), string[128];

		if(amount == 0) 
			return SCM(playerid, -1, "Error");

		switch(GetPVarInt(playerid, "typeDepositWithdraw")) 
		{
			case 1:
			{
				if(amount > GetPlayerCash(playerid))
			        return SendClientMessage(playerid, COLOR_GRAD2, "   You don't have that much.");
			    
			    GivePlayerCash(playerid,-amount);
			    new curfunds = PlayerInfo[playerid][pBank];
			    PlayerInfo[playerid][pBank]=amount+PlayerInfo[playerid][pBank];
			    SendClientMessage(playerid, COLOR_WHITE, "|___ BANK STATMENT ___|");
			    format(string, sizeof(string), "  Old Balance: $%d", curfunds);
			    SendClientMessage(playerid, COLOR_GRAD2, string);
			    format(string, sizeof(string), "  Deposit: $%d",amount);
			    SendClientMessage(playerid, COLOR_GRAD4, string);
			    SendClientMessage(playerid, COLOR_GRAD6, "|-----------------------------------------|");
			    format(string, sizeof(string), "  New Balance: $%d", PlayerInfo[playerid][pBank]);
			    SendClientMessage(playerid, COLOR_WHITE, string);
			}
			case 2: 
			{
				if(amount > PlayerInfo[playerid][pBank])
			    	return SendClientMessage(playerid, COLOR_GRAD2, "   You don't have that much!");

			    GivePlayerCash(playerid,amount);
			    PlayerInfo[playerid][pBank]=PlayerInfo[playerid][pBank]-amount;
			    format(string, sizeof(string), "  You have withdrawn $%d from your account. Current balance: $%d ", amount,PlayerInfo[playerid][pBank]);
			    SendClientMessage(playerid, COLOR_YELLOW, string);
			}
			case 3: 
			{
				new giveplayerid = GetPVarInt(playerid, "givePlayerID"), amount = GetPVarInt(playerid, "bankDepositValue");
				if(IsPlayerConnected(giveplayerid))
			    {
			        if(giveplayerid != INVALID_PLAYER_ID)
			        {
			            new playermoney = PlayerInfo[playerid][pBank] ;
			            if(amount > 0 && playermoney >= amount)
			            {
			                PlayerInfo[playerid][pBank] -= amount;
			                PlayerInfo[giveplayerid][pBank] += amount;
			                format(string, sizeof(string), "   You have transferred $%d to %s's account.", amount, GetPlayerNameEx(giveplayerid),giveplayerid);
			                PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			                SendClientMessage(playerid, COLOR_GRAD1, string);
			                format(string, sizeof(string), "   You have recieved $%d to into your account from %s.", amount, GetPlayerNameEx(playerid), playerid);
			                SendClientMessage(giveplayerid, COLOR_GRAD1, string);
			                new ip[32], ipex[32];
			                GetPlayerIp(playerid, ip, sizeof(ip));
			                GetPlayerIp(giveplayerid, ipex, sizeof(ipex));
			                format(string, sizeof(string), "[BANK] %s (IP:%s) has transferred $%d to %s (IP:%s).", GetPlayerNameEx(playerid), ip, amount, GetPlayerNameEx(giveplayerid), ipex);

			                if(amount >= 500000)
			                {
			                    ABroadCast(COLOR_YELLOW,string,2);
			                }
			                Log("logs/pay.log", string);
			                PlayerPlaySound(giveplayerid, 1052, 0.0, 0.0, 0.0);
			            }
			            else
			            {
			                SendClientMessage(playerid, COLOR_GRAD1, "   Invalid transaction amount.");
			            }
			        }
			    }
			    else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player specified.");
			}
		}
	}

	if(playertextid == BankTextdraw_OP_1[18])
	{
		PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[1], -1370687745), hideBankGUI_Page(playerid, 1), showBankGUI_Page(playerid, 2), SetPVarInt(playerid, "bankDepositValue", 0), PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[8], "~G~$0"), SetPVarInt(playerid, "typeDepositWithdraw", 2);
		PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[2], "WITHDRAW MONEY"), PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[7], "How much do you want to withdraw"),
		PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[11], "  Your withdraw"); 
	}

	if(playertextid == BankTextdraw_OP_1[21])
	{
		PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[1], -5963521), hideBankGUI_Page(playerid, 1), showBankGUI_Page(playerid, 3), SetPVarInt(playerid, "bankDepositValue", 0), SetPVarInt(playerid, "typeDepositWithdraw", 3), SetPVarInt(playerid, "givePlayerID", 0xFFFF);
		PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[2], "TRANSFER MONEY"), PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[11], "  Your transfer"), PlayerTextDrawSetString(playerid, BankTextdraw_OP_3[2], "~G~$0"), PlayerTextDrawSetString(playerid, BankTextdraw_OP_3[5], "~G~ID");
	}
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid) 
	{
		case BANKDEPOSIT: 
		{
			if(!response)
				return 1;

			new const amount = strval(inputtext);

			if(!IsNumeric(inputtext)) 
				return SCM(playerid, -1, "You need to put a value.");

			if(amount > (GetPVarInt(playerid, "typeDepositWithdraw") == 1 ? GetPlayerCash(playerid) : PlayerInfo[playerid][pBank]) || amount < 0)
		        return SendClientMessage(playerid, COLOR_GRAD2, "   You don't have that much.");

		    SetPVarInt(playerid, "bankDepositValue", amount);
		    new str[64];
		    format(str, 64, "~G~$%d", amount);
		    PlayerTextDrawSetString(playerid, BankTextdraw_OP_2[8], str), PlayerTextDrawSetString(playerid, BankTextdraw_OP_3[2], str); 
		}
		case SETPLAYERID: 
		{
			if(!response)
				return 1;

			if(!IsNumeric(inputtext) || !IsPlayerConnected(strval(inputtext)) || strval(inputtext) == playerid)
				return SCM(playerid, -1, "You need to put a valid player id.");

			new const amount = strval(inputtext);

			SetPVarInt(playerid, "givePlayerID", amount);
		    new str[64];
		    format(str, 64, "~G~%d", amount);
		    PlayerTextDrawSetString(playerid, BankTextdraw_OP_3[5], str);
		}
	}
	return 1;
}

public OnPlayerConnect(playerid) 
{	
	bankTextdraws[playerid][showed] = false;
	initPlayerBankTextdraws(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason) 
{	
	destroyPlayerBankTextdraws(playerid);
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) 
{
	if(clickedid == INVALID_TEXT_DRAW && bankTextdraws[playerid][showed]) 
		return SelectTextDraw(playerid, -1);

	return 1;
}*/

stock showBankGUI_Page(const playerid, const page)
{
	switch(page) 
	{
		case 0: 
		{
			for(new i = 0; i <= 5; ++i) PlayerTextDrawShow(playerid, BankTextdraw_OP_0[i]);
		}
		case 1: 
		{
			for(new i = 0; i <= 23; ++i) PlayerTextDrawShow(playerid, BankTextdraw_OP_1[i]); 
		}
		case 2: 
		{
			for(new i = 0; i <= 5; ++i) PlayerTextDrawShow(playerid, BankTextdraw_OP_1[i]);
			for(new i = 0; i <= 11; ++i) PlayerTextDrawShow(playerid, BankTextdraw_OP_2[i]);
		}
		case 3: 
		{
			for(new i = 0; i <= 5; ++i) PlayerTextDrawShow(playerid, BankTextdraw_OP_1[i]), PlayerTextDrawShow(playerid, BankTextdraw_OP_2[i]), PlayerTextDrawShow(playerid, BankTextdraw_OP_3[i]);
			PlayerTextDrawShow(playerid, BankTextdraw_OP_2[9]), PlayerTextDrawShow(playerid, BankTextdraw_OP_2[10]), PlayerTextDrawShow(playerid, BankTextdraw_OP_2[11]);
		}
	}
	new str[64];
	format(str, 64, "~G~$%d", PlayerInfo[playerid][pBank]);
	PlayerTextDrawSetString(playerid, BankTextdraw_OP_1[9], str);
	return 1;
}

stock hideBankGUI_Page(const playerid, const page)
{
	switch(page) 
	{
		case 0: 
		{
			for(new i = 0; i <= 5; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_0[i]);
		}
		case 1: 
		{
			for(new i = 0; i <= 23; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_1[i]);
		}
		case 2: 
		{
			for(new i = 0; i <= 5; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_1[i]);
			for(new i = 0; i <= 11; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_2[i]);
		}
		case 3: 
		{
			for(new i = 0; i <= 5; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_1[i]), PlayerTextDrawHide(playerid, BankTextdraw_OP_2[i]), PlayerTextDrawHide(playerid, BankTextdraw_OP_3[i]);
			PlayerTextDrawHide(playerid, BankTextdraw_OP_2[9]), PlayerTextDrawHide(playerid, BankTextdraw_OP_2[10]), PlayerTextDrawHide(playerid, BankTextdraw_OP_2[11]);
		}
	}
	return 1;
}

stock hideBankGUI(const playerid) 
{
	for(new i = 0; i <= 5; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_0[i]), PlayerTextDrawHide(playerid, BankTextdraw_OP_3[i]);
	for(new i = 0; i <= 23; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_1[i]);
	for(new i = 0; i <= 11; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_2[i]);
	return 1;
}

CMD:pl(playerid, params[]) return PlayerInfo[playerid][pBank] += 1000;

stock initPlayerBankTextdraws(const playerid) 
{
	BankTextdraw_OP_0[0] = CreatePlayerTextDraw(playerid, 159.000000, 81.733268, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_0[0], 0.000000, 28.300004);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_0[0], 483.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_0[0], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_0[0], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_0[0], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_0[0], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[0], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_0[0], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_0[0], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_0[0], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_0[0], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[0], 0);

	BankTextdraw_OP_0[1] = CreatePlayerTextDraw(playerid, 159.000000, 81.733245, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_0[1], 0.000000, 17.800010);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_0[1], 483.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_0[1], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_0[1], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_0[1], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_0[1], 2046050559);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[1], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_0[1], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_0[1], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_0[1], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_0[1], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[1], 0);

	BankTextdraw_OP_0[2] = CreatePlayerTextDraw(playerid, 320.000000, 107.866577, "ATM BY LATEX");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_0[2], 0.671500, 4.026667);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_0[2], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_0[2], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[2], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_0[2], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_0[2], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_0[2], 2);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_0[2], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[2], 0);

	BankTextdraw_OP_0[3] = CreatePlayerTextDraw(playerid, 245.299987, 147.066619, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_0[3], 0.000000, 0.511001);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_0[3], 395.500030, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_0[3], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_0[3], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_0[3], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_0[3], -16776961);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[3], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_0[3], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_0[3], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_0[3], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_0[3], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[3], 0);

	BankTextdraw_OP_0[4] = CreatePlayerTextDraw(playerid, 318.800231, 185.689147, "~R~Please ~W~~H~connect~N~by the help ~R~of~W~~H~ your fingerprint");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_0[4], 0.293000, 1.680889);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_0[4], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_0[4], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[4], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_0[4], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_0[4], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_0[4], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_0[4], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[4], 0);

	BankTextdraw_OP_0[5] = CreatePlayerTextDraw(playerid, 294.000000, 263.778015, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_0[5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_0[5], 50.000000, 48.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_0[5], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_0[5], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[5], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_0[5], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_0[5], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_0[5], 4);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_0[5], 0);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_0[5], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_0[5], true);

	BankTextdraw_OP_1[0] = CreatePlayerTextDraw(playerid, 159.000000, 81.733268, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[0], 0.000000, 28.300004);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[0], 483.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[0], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[0], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[0], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[0], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[0], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[0], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[0], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[0], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[0], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[0], 0);

	BankTextdraw_OP_1[1] = CreatePlayerTextDraw(playerid, 159.000000, 81.733245, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[1], 0.000000, 3.158037);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[1], 482.888916, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[1], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[1], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[1], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[1], 2046050559);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[1], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[1], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[1], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[1], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[1], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[1], 0);

	BankTextdraw_OP_1[2] = CreatePlayerTextDraw(playerid, 162.000000, 86.088790, "MAZE BANK");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[2], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[2], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[2], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[2], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[2], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[2], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[2], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[2], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[2], 0);

	BankTextdraw_OP_1[3] = CreatePlayerTextDraw(playerid, 165.200012, 104.133209, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[3], 235.000061, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[3], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[3], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[3], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[3], -16776961);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[3], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[3], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[3], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[3], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[3], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[3], 0);

	BankTextdraw_OP_1[4] = CreatePlayerTextDraw(playerid, 402.500000, 89.822257, "Would you like to disconnect?");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[4], 0.222000, 1.127110);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[4], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[4], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[4], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[4], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[4], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[4], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[4], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[4], 0);

	BankTextdraw_OP_1[5] = CreatePlayerTextDraw(playerid, 463.200042, 88.055488, "LD_BEAT:cross");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[5], 14.000000, 16.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[5], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[5], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[5], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[5], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[5], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[5], 4);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[5], 0);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[5], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_1[5], true);

	BankTextdraw_OP_1[6] = CreatePlayerTextDraw(playerid, 179.099639, 133.221740, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[6], 0.000000, 15.249994);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[6], 357.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[6], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[6], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[6], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[6], -1061109505);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[6], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[6], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[6], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[6], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[6], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[6], 0);

	BankTextdraw_OP_1[7] = CreatePlayerTextDraw(playerid, 190.000000, 139.599945, "Welcome~N~~G~~H~John_Cluny2");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[7], 0.325999, 1.375999);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[7], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[7], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[7], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[7], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[7], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[7], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[7], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[7], 0);

	BankTextdraw_OP_1[8] = CreatePlayerTextDraw(playerid, 190.000000, 183.155502, "You have");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[8], 0.263999, 1.326221);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[8], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[8], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[8], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[8], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[8], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[8], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[8], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[8], 0);

	BankTextdraw_OP_1[9] = CreatePlayerTextDraw(playerid, 190.000000, 195.466552, "~G~$100000000");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[9], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[9], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[9], 8388863);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[9], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[9], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[9], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[9], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[9], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[9], 0);

	BankTextdraw_OP_1[10] = CreatePlayerTextDraw(playerid, 179.499969, 285.200073, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[10], 0.000000, 4.799999);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[10], 296.499969, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[10], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[10], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[10], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[10], -1061109505);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[10], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[10], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[10], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[10], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[10], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[10], 0);

	BankTextdraw_OP_1[11] = CreatePlayerTextDraw(playerid, 217.500000, 285.822296, "YOU CAN TRUST US");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[11], 0.232500, 1.214221);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[11], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[11], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[11], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[11], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[11], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[11], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[11], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[11], 0);

	BankTextdraw_OP_1[12] = CreatePlayerTextDraw(playerid, 182.100097, 299.188964, "The number of BNP Panbas~N~account creation has increased~N~by 7% since 2017.");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[12], 0.158500, 0.946666);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[12], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[12], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[12], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[12], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[12], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[12], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[12], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[12], 0);

	BankTextdraw_OP_1[13] = CreatePlayerTextDraw(playerid, 260.300018, 284.555725, "LD_BEAT:cring");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[13], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[13], 43.000000, 45.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[13], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[13], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[13], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[13], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[13], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[13], 4);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[13], 0);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[13], 0);

	BankTextdraw_OP_1[14] = CreatePlayerTextDraw(playerid, 275.000091, 302.366699, "~G~+ 7%");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[14], 0.160499, 0.940444);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[14], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[14], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[14], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[14], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[14], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[14], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[14], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[14], 0);

	BankTextdraw_OP_1[15] = CreatePlayerTextDraw(playerid, 370.899780, 133.455535, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[15], 0.000000, 4.399996);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[15], 474.899993, 15.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[15], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[15], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[15], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[15], 998552575);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[15], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[15], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[15], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[15], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[15], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[15], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_1[15], true);

	BankTextdraw_OP_1[16] = CreatePlayerTextDraw(playerid, 374.500000, 133.377716, "DEPOSIT");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[16], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[16], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[16], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[16], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[16], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[16], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[16], 2);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[16], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[16], 0);

	BankTextdraw_OP_1[17] = CreatePlayerTextDraw(playerid, 374.500000, 150.833404, "Your money is save here");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[17], 0.229000, 1.064888);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[17], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[17], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[17], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[17], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[17], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[17], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[17], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[17], 0);

	BankTextdraw_OP_1[18] = CreatePlayerTextDraw(playerid, 370.999786, 187.958862, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[18], 0.000000, 4.399996);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[18], 475.000000, 15.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[18], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[18], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[18], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[18], -1370687745);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[18], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[18], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[18], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[18], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[18], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[18], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_1[18], true);

	BankTextdraw_OP_1[19] = CreatePlayerTextDraw(playerid, 374.500000, 187.180999, "WITHDRAW");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[19], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[19], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[19], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[19], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[19], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[19], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[19], 2);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[19], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[19], 0);

	BankTextdraw_OP_1[20] = CreatePlayerTextDraw(playerid, 374.500000, 202.236541, "We will give the money~N~back you stored");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[20], 0.229000, 1.064888);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[20], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[20], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[20], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[20], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[20], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[20], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[20], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[20], 0);

	BankTextdraw_OP_1[21] = CreatePlayerTextDraw(playerid, 370.999786, 243.262237, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[21], 0.000000, 4.399996);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_1[21], 475.000000, 15.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[21], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[21], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_1[21], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_1[21], -5963521);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[21], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[21], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[21], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[21], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[21], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[21], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_1[21], true);

	BankTextdraw_OP_1[22] = CreatePlayerTextDraw(playerid, 372.899902, 240.484252, "TRANSFER");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[22], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[22], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[22], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[22], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[22], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[22], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[22], 2);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[22], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[22], 0);

	BankTextdraw_OP_1[23] = CreatePlayerTextDraw(playerid, 374.500000, 255.539794, "Give your money to~N~someone else");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_1[23], 0.229000, 1.064888);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_1[23], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_1[23], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[23], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_1[23], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_1[23], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_1[23], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_1[23], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_1[23], 0);

	BankTextdraw_OP_2[0] = CreatePlayerTextDraw(playerid, 257.199707, 153.911071, "We are the most secure bank of the city");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[0], 0.256500, 1.164443);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[0], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[0], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[0], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[0], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[0], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[0], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[0], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[0], 0);

	BankTextdraw_OP_2[1] = CreatePlayerTextDraw(playerid, 167.799743, 132.133316, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[1], 0.000000, 5.150002);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_2[1], 368.799743, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[1], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[1], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_2[1], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[1], 1235677951);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[1], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[1], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[1], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[1], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[1], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[1], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_2[1], true);

	BankTextdraw_OP_2[2] = CreatePlayerTextDraw(playerid, 170.499664, 136.978271, "DEPOSIT YOUR MONEY");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[2], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[2], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[2], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[2], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[2], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[2], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[2], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[2], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[2], 0);

	BankTextdraw_OP_2[3] = CreatePlayerTextDraw(playerid, 386.000000, 132.211090, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[3], 0.000000, 5.121996);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_2[3], 478.000000, 15.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[3], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[3], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_2[3], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[3], -2139062017);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[3], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[3], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[3], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[3], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[3], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[3], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_2[3], true);

	BankTextdraw_OP_2[4] = CreatePlayerTextDraw(playerid, 389.799377, 136.978271, "RETURN");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[4], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[4], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[4], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[4], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[4], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[4], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[4], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[4], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[4], 0);

	BankTextdraw_OP_2[5] = CreatePlayerTextDraw(playerid, 427.300750, 153.911071, "To the main menu");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[5], 0.256500, 1.164443);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[5], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[5], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[5], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[5], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[5], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[5], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[5], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[5], 0);

	BankTextdraw_OP_2[6] = CreatePlayerTextDraw(playerid, 167.999816, 201.200012, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[6], 0.000000, 7.749996);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_2[6], 478.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[6], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[6], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_2[6], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[6], -1061109505);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[6], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[6], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[6], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[6], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[6], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[6], 0);

	BankTextdraw_OP_2[7] = CreatePlayerTextDraw(playerid, 175.500000, 208.044464, "How much do you want to deposit");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[7], 0.217000, 1.220444);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[7], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[7], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[7], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[7], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[7], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[7], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[7], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[7], 0);

	BankTextdraw_OP_2[8] = CreatePlayerTextDraw(playerid, 322.403320, 225.077941, "~G~$0");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[8], 0.596997, 3.261332);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_2[8], 15.000000, 154.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[8], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[8], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_2[8], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[8], 0);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[8], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[8], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[8], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[8], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[8], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[8], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_2[8], true);

	BankTextdraw_OP_2[9] = CreatePlayerTextDraw(playerid, 168.000000, 286.100158, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[9], 0.000000, 4.850000);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_2[9], 271.000000, 15.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[9], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[9], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_2[9], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_2[9], 8388863);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[9], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[9], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[9], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[9], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[9], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[9], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_2[9], true);

	BankTextdraw_OP_2[10] = CreatePlayerTextDraw(playerid, 171.500000, 288.311187, "VALIDATE");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[10], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[10], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[10], -1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[10], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[10], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[10], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[10], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[10], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[10], 0);

	BankTextdraw_OP_2[11] = CreatePlayerTextDraw(playerid, 198.800750, 304.733367, "Your Deposit");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_2[11], 0.256500, 1.164443);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_2[11], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_2[11], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[11], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_2[11], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_2[11], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_2[11], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_2[11], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_2[11], 0);

	BankTextdraw_OP_3[0] = CreatePlayerTextDraw(playerid, 168.000000, 193.111114, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_3[0], 0.000000, 7.763994);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_3[0], 309.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_3[0], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_3[0], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_3[0], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_3[0], -1061109505);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[0], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_3[0], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_3[0], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_3[0], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_3[0], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[0], 0);

	BankTextdraw_OP_3[1] = CreatePlayerTextDraw(playerid, 174.500000, 201.344390, "How much do you want to give?");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_3[1], 0.187000, 1.195556);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_3[1], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_3[1], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[1], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_3[1], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_3[1], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_3[1], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_3[1], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[1], 0);

	BankTextdraw_OP_3[2] = CreatePlayerTextDraw(playerid, 232.500000, 219.966674, "~G~$0");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_3[2], 0.477499, 2.564444);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_3[2], 10.000000, 87.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_3[2], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_3[2], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_3[2], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_3[2], 0);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[2], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_3[2], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_3[2], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_3[2], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_3[2], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[2], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_3[2], true);

	BankTextdraw_OP_3[3] = CreatePlayerTextDraw(playerid, 330.204895, 193.111114, "box");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_3[3], 0.000000, 7.649998);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_3[3], 472.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_3[3], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_3[3], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_3[3], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_3[3], -1061109505);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[3], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_3[3], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_3[3], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_3[3], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_3[3], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[3], 0);

	BankTextdraw_OP_3[4] = CreatePlayerTextDraw(playerid, 336.000122, 200.722167, "Who would you like to transfer to?");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_3[4], 0.187000, 1.195556);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_3[4], 1);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_3[4], 255);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[4], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_3[4], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_3[4], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_3[4], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_3[4], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[4], 0);

	BankTextdraw_OP_3[5] = CreatePlayerTextDraw(playerid, 403.000000, 220.966735, "~g~ID");
	PlayerTextDrawLetterSize(playerid, BankTextdraw_OP_3[5], 0.477499, 2.564444);
	PlayerTextDrawTextSize(playerid, BankTextdraw_OP_3[5], 10.000000, 93.000000);
	PlayerTextDrawAlignment(playerid, BankTextdraw_OP_3[5], 2);
	PlayerTextDrawColor(playerid, BankTextdraw_OP_3[5], -1);
	PlayerTextDrawUseBox(playerid, BankTextdraw_OP_3[5], 1);
	PlayerTextDrawBoxColor(playerid, BankTextdraw_OP_3[5], 0);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[5], 0);
	PlayerTextDrawSetOutline(playerid, BankTextdraw_OP_3[5], 0);
	PlayerTextDrawBackgroundColor(playerid, BankTextdraw_OP_3[5], 255);
	PlayerTextDrawFont(playerid, BankTextdraw_OP_3[5], 1);
	PlayerTextDrawSetProportional(playerid, BankTextdraw_OP_3[5], 1);
	PlayerTextDrawSetShadow(playerid, BankTextdraw_OP_3[5], 0);
	PlayerTextDrawSetSelectable(playerid, BankTextdraw_OP_3[5], true);
	return 1;
}

stock destroyPlayerBankTextdraws(const playerid) 
{
	for(new i = 0; i <= 5; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_0[i]), PlayerTextDrawHide(playerid, BankTextdraw_OP_3[i]);
	for(new i = 0; i <= 23; ++i) PlayerTextDrawHide(playerid, BankTextdraw_OP_1[i]);
	for(new i = 0; i <= 11; ++i) PlayerTextDrawShow(playerid, BankTextdraw_OP_2[i]);
	return 1;
}