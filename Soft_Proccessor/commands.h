DEF_CMD(PUSH, 65, {
					REC(numCom, 'c');

                    ASM_FORMAT("%s %s", com, reg);
                    
                    if (reg[0] == '[') {
                        if (reg[1] >= '0' && reg[1] <= '9') {
                            REC(MD_PUSH_FROM_RAM, 'c');
                            
                            ASM_FORMAT("%s [%d]", com, &var);

                            REC(var, 'i');
                            
                            break;
                        }
                    
                        ASM_FORMAT("%s [%3s]", com, reg);

                        WHICH_REG(MD_PUSH_FROM_RAM_REG);
                        
                        break;
                    }
                    
                    if (reg[0] == 'r') {
						WHICH_REG(MD_PUSH_REG);
                        
                        break;
                    }
                        
                    if (reg[0] >= '0' && reg[0] <= '9') {
                        ASM_FORMAT("%s %d", com, &var);

                        REC(MD_PUSH_INT, 'c');

                        REC(var, 'i');
                        
                        break;
                    }

                    printf("Invalid line!\n"); 
                    
				  },

                  {
                        pc += sizeof(char);

                        switch (bytecode[pc]) {
                            case MD_PUSH_REG:
                             	PC('c');

                                PUUSH(REEG);

                                PC('i');

                                break;

                            case MD_PUSH_INT:
                                PC('c');

                                PUUSH(CUR_SHIFT);

                                PC('i');

                                break;

                            case MD_PUSH_FROM_RAM:
                                PC('c');

                                PUUSH(RAAAM(CUR_SHIFT));

                                PC('i');

                                sleep(1);

                                break;

                            case MD_PUSH_FROM_RAM_REG:
                                PC('c');

                                PUUSH(RAAAM(REEG));

                                PC('i');

                                sleep(1);

                                break;
                        }  
                  } ) // A

DEF_CMD(POP, 66, {
		            REC(numCom, 'c');

		            if (ASM_FORMAT("%s %s", com, reg) == 1) {
		                REC(MD_POP_FROM, 'c');

		                break;
		            }

		            if (reg[0] == '[') {
		                if (reg[1] >= '0' && reg[1] <= '9') {
		                    REC(MD_POP_IN_RAM, 'c');

		                    ASM_FORMAT("%s [%d]", com, &var);

		                    REC(var, 'i');

		                    break;
		                }

		                ASM_FORMAT("%s [%3s]", com, reg);

		                WHICH_REG(MD_POP_IN_RAM_REG);

		                break;
		            }

		            if (reg[0] == 'r') {
		                WHICH_REG(MD_POP_IN_REG);

		                break;
		            }

		            printf("Invalid line!\n");
				 },
				  
				 {
				 	pc += sizeof(char);

	                switch (bytecode[pc]) {
	                    case MD_POP_FROM:
	                        PC('c');

	                        POOP();

	                        PC('c');

	                        break;

	                    case MD_POP_IN_REG:
	                        PC('c');

	                        REEG = POOP();

	                        PC('i');

	                        break;

	                    case MD_POP_IN_RAM:
	                        PC('c');

	                       	RAAAM(CUR_SHIFT) = POOP();

	                        PC('i');

	                        sleep(1);

	                        break;

	                    case MD_POP_IN_RAM_REG:
	                        PC('c');

	                        RAAAM(REEG) = POOP();

	                        PC('i');

	                        sleep(1);

	                        break;
	                }
				 } ) // B

DEF_CMD(MUL, 67, {
            	   	REC(numCom, 'c');
            	 },

            	 {
            	 	PUUSH(POOP() * POOP());
               	   	PC('c');
               	 } )  // C

DEF_CMD(ADD, 68, {
					REC(numCom, 'c');
            	 },

            	 {
            	 	PUUSH(POOP() + POOP());
                	PC('c');
            	 } ) // D

DEF_CMD(OUT, 69, {
					REC(numCom, 'c'); 
            	 },

            	 {
            	 	printf("%d\n", POOP());

                	PC('c');
            	 } ) // E

DEF_CMD(END, 70, {
					REC(numCom, 'c');
            	 },

            	 {

            	 } ) // F

DEF_CMD(DIV, 71, {
					REC(numCom, 'c'); 
            	 },

            	 {
            	 	prom = POOP();
                	PUUSH(POOP() / prom);

                	PC('c');
            	 } ) // G

DEF_CMD(SUB, 72, {
					REC(numCom, 'c'); 
            	 },

            	 {
            	 	prom = POOP();
                	PUUSH(POOP() - prom);

                	PC('c');
            	 } ) // H

DEF_CMD(IN, 73, { 
					REC(numCom, 'c');
            	}, 

            	{
            		printf("Please, enter the number:\n");

                	scanf("%d", &prom);
                	PUUSH(prom);

                	PC('c');
            	} ) // I

DEF_CMD(SQRT, 74, {
					REC(numCom, 'c');
            	  },

            	  {
            	 	PUUSH( SqRt(POOP()) );

                	PC('c');
            	  } ) // J

DEF_CMD(JMP, 75, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				 },

				 {
				 	PC('c');

                	PC(CUR_SHIFT);
				 } ) // K

DEF_CMD(JA, 76, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				},

				{
					prom = POOP();
	                PC('c');

	                if (prom > POOP()) {
	                    PC(CUR_SHIFT);

	                    break;
	                }

	                PC('i');
				} ) // L Last > pre-Last

DEF_CMD(JB, 77, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				},

				{
					prom = POOP();
                	PC('c');

                	if (prom < POOP()) {
                    	PC(CUR_SHIFT);

                    	break;
                	}

                	PC('i');
				} ) // M Last < pre-Last

DEF_CMD(JC, 78, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				},

				{
					prom = POOP();
                	PC('c');

                	if (prom == POOP()) {
                    	PC(CUR_SHIFT);

                    	break;
                	}

                	PC('i');
				} ) // N ==

DEF_CMD(JAC, 79, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				 },

				 {
				 	prom = POOP();
                	PC('c');

                	if (prom >= POOP()) {
                    	PC(CUR_SHIFT);

                    	break;
                	}

                	PC('i');
				 } ) // O >=

DEF_CMD(JBC, 80, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				 },

				 {
				 	prom = POOP();
                	PC('c');

                	if (prom <= POOP()) {
                    	PC(CUR_SHIFT);

                    	break;
                	}

                	PC('i');
				 } ) // P <=

DEF_CMD(JRC, 81, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				 },

				 {
				 	prom = POOP();
                	PC('c');

                	if (prom != POOP()) {
                    	PC(CUR_SHIFT);

                    	break;
                	}

                	PC('i');
				 } ) // Q !=

DEF_CMD(CALL, 82, {
					ASM_FORMAT("%s :%d", com, &var);
            		REC(numCom, 'c');

            		REC(Ded32[var], 'i');
				 },

				 {
				 	PC('c');

	                CALL();

	                PC(CUR_SHIFT);
				 } ) // R

DEF_CMD(RET, 83, {
					REC(numCom, 'c');
            	 },

            	 {
            	 	REET();
            	 } ) // S

DEF_CMD(CAT, 84, {
					REC(numCom, 'c'); 
            	 },

            	 {
            	 	printf("                   /\\             /\\\n"
	                       "                  |`\\\\_,--=\"=--,_//`|  \n"
	                       "                  \\ .\"  :'. .':  \". /\n"
	                       "                 ==)  _ :  '  : _  (==\n"
	                       "                   |>/O\\   _   /O\\<|\n"
	                       "                   | \\-\"~` _ `~\"-/ |\n"
	                       "                  >|`===. \\_/ .===`|<\n"
	                       "        Ded .-\"-.   \\==='  |  '===/   .-\"-.\n"
	                       "     .-----{'. '`}---\\,  .-'-.  ,/---{.'. '}-----.\n"
	                       "     |     `\"---\"`     `~-===-~`     `\"---\"`     |\n"
	                       "     |     .-------------------------------.     |\n"
	                       "     |     |                               |     |\n"
	                       "     |     |                               |     |\n"
	                       "     |     |                    .--.       |     |\n"
	                       "     |     |                  .\"  o \\__    |     |\n"
	                       "     |     |               _.-\"    ,(  `   |     |\n"
	                       "     |     |           _.-\"      ,;;|      |     |\n"
	                       "     |     |      _.-=\" _,\"    ,,;;;'      |     |\\  \n"
	                       "     |     |  .-\"`_.-\"``-..,,;;;;:'        |     |'\\\n"
	                       "     |     |  `\"'`          `\\`\\           |     |.'`\\\n"
	                       "     |     |                 /^\\\\\\         |     |'.'`}\n"
	                       "     |     |                               |     } '. }\n"
	                       "     |     |                               |    /.'`./\n"
	                       "     |     '-------------------------------'   /. './\n"
	                       "    _|  _                                     /.`'./\n"
	                       "   (.\\-/.)--------.__________________.-------{.'. {\n"
	                       "    \\0 0/         /                  \\       `\\.'`\\\n"
	                       "(   =\\ /=  ______/....................\\______  \\.'.\\\n"
	                       " \\   /o\\  |                                  |  }'.'}\n"
	                       "  ) /   \\ | [[[[[[[[[[ ===       ()  ()  ()  | {'.'/\n"
	                       " (  U   U |                       ________   |  `~`\n"
	                       "  \\(|   |)| [[[[[[[[[[ ===       [________]  |\n"
	                       "   _w___w_:----------------------------------:_______\n"
	                       "  |  []  [][][][] [][][][] [][][][] [][][]  == ===== |\n"
	                       "  |                                                  |\n"
	                       "  |   [][][][][][][][][][][][][][]_ [][][] [][][][]  |\n"
	                       "  |   [_][][][][][][][][][][][][]| |[][][] [][][]||  |\n"
	                       "  |   []  [][][][][][][][][][][][__|       [][][]||  |\n"
	                       "  |   [__] [][][][][][][][][][][___]  []   [][][]||  |\n"
	                       "  |   [_]  [_][_____________][_] [_][][][] [__][]||  |\n"
	                       "  '--------------------------------------------------'\n");

                	PC('c');
            	 } ) // T




DEF_MD(PUSH_REG, 33) // !
DEF_MD(PUSH_INT, 34) // "
DEF_MD(POP_FROM, 35) // #
DEF_MD(POP_IN_REG, 36) // $
DEF_MD(PUSH_FROM_RAM, 37) // %
DEF_MD(PUSH_FROM_RAM_REG, 38) // &
DEF_MD(POP_IN_RAM, 39) // '
DEF_MD(POP_IN_RAM_REG, 40) // (




DEF_REG(RAX, 97) // 61 00 00 00
DEF_REG(RBX, 98) // 62 00 00 00
DEF_REG(RCX, 99) // 63 00 00 00
DEF_REG(RDX, 100) // 64 00 00 00
DEF_REG(REX, 101) // 65 00 00 00


