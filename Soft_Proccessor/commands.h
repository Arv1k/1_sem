DEF_CMD(PUSH, 65, {
					bytecode[*pc] = numCom;
                    *pc += sizeof(char);
                    
                    sscanf(str, "%s %s", com, reg);
                    
                    if (reg[0] == '[') {
                        if (reg[1] >= '0' && reg[1] <= '9') {
                            bytecode[*pc] = MD_PUSH_FROM_RAM;
                            *pc += sizeof(char);
                            
                            sscanf(str, "%s [%d]", com, &var);
                            
                            ((int *) (bytecode + *pc))[0] = var;
                            *pc += sizeof(int);
                            
                            break;
                        }
                    
                        sscanf(str, "%s [%s]", com, reg);
                        
                        reg_num = which_reg(reg);
                        if (reg_num == yad) {
                            printf("Invalid register!\n");
                            abort(); //change to assert
                        }
                    
                        bytecode[*pc] = MD_PUSH_FROM_RAM;
                        *pc += sizeof(char);
                        
                        ((int *) (bytecode + *pc))[0] = reg_num;
                        *pc += sizeof(int);
                        
                        break;
                    }
                    
                    if (reg[0] == 'r') {
                        reg_num = which_reg(reg);
                        if (reg_num == yad) {
                            printf("Invalid register!\n");
                            abort(); //change to assert
                        }
                        
                        bytecode[*pc] = MD_PUSH_REG;
                        *pc += sizeof(char);
                        
                        ((int *) (bytecode + *pc))[0] = reg_num;
                        *pc += sizeof(int);
                        
                        break;
                    }
                        
                    if (reg[0] >= '0' && reg[0] <= '9') {
                        sscanf(str, "%s %d", com, &var);
                        
                        bytecode[*pc] = MD_PUSH_INT;
                        *pc += sizeof(char);
                        
                        ((int *) (bytecode + *pc))[0] = var;
                        *pc += sizeof(int);
                        
                        break;
                    }

                    printf("Invalid line!\n"); 
                    
				  },

                  {
                        pc += sizeof(char);

                        switch (bytecode[pc]) {
                            case MD_PUSH_REG:
                                pc += sizeof(char);

                                StackPush(&processor->stProc,
                                           processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ]);

                                pc += sizeof(int);

                                break;

                            case MD_PUSH_INT:
                                pc += sizeof(char);

                                StackPush(&processor->stProc,
                                          ((int *) (bytecode + pc))[0]);

                                pc += sizeof(int);

                                break;

                            case MD_PUSH_FROM_RAM:
                                pc += sizeof(char);

                                StackPush(&processor->stProc,
                                           processor->operation_mem[ ((int *) (bytecode + pc)) [0] ]);

                                pc += sizeof(int);

                                sleep(1);

                                break;

                            case MD_PUSH_FROM_RAM_REG:
                                pc += sizeof(char);

                                StackPush(&processor->stProc,
                                           processor->operation_mem
                                           [ processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ] ]);

                                pc += sizeof(int);

                                sleep(1);

                                break;
                        }  
                  } ) // A

DEF_CMD(POP, 66, {
					bytecode[*pc] = numCom;
		            *pc += sizeof(char);

		            if (sscanf(str, "%s %s", com, reg) == 1) {
		                bytecode[*pc] = MD_POP_FROM;
		                *pc += sizeof(char);

		                break;
		            }

		            if (reg[0] == '[') {
		                if (reg[1] >= '0' && reg[1] <= '9') {
		                    bytecode[*pc] = MD_POP_IN_RAM;
		                    *pc += sizeof(char);

		                    sscanf(str, "%s [%d]", com, &var);

		                    ((int *) (bytecode + *pc))[0] = var;
		                    *pc += sizeof(int);

		                    break;
		                }

		                sscanf(str, "%s [%s]", com, reg);

		                reg_num = which_reg(reg);
		                if (reg_num == yad) {
		                    printf("Invalid register!\n");
		                    abort(); //change to assert
		                }

		                bytecode[*pc] = MD_POP_IN_RAM_REG;
		                *pc += sizeof(char);

		                ((int *) (bytecode + *pc))[0] = reg_num;
		                *pc += sizeof(int);

		                break;
		            }

		            if (reg[0] == 'r') {
		                reg_num = which_reg(reg);
		                if (reg_num == yad) {
		                    printf("Invalid register!\n");
		                    abort(); //change to assert
		                }

		                bytecode[*pc] = MD_POP_IN_REG;
		                *pc += sizeof(char);

		                ((int *) (bytecode + *pc))[0] = reg_num;
		                *pc += sizeof(int);

		                break;
		            }

		            printf("Invalid line!\n");
				 },
				  
				 {
				 	pc += sizeof(char);

	                switch (bytecode[pc]) {
	                    case MD_POP_FROM:
	                        pc += sizeof(char);

	                        StackPop(&processor->stProc);

	                        pc += sizeof(char);

	                        break;

	                    case MD_POP_IN_REG:
	                        pc += sizeof(char);

	                        processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ] = StackPop(&processor->stProc);

	                        pc += sizeof(int);

	                        break;

	                    case MD_POP_IN_RAM:
	                        pc += sizeof(char);

	                        processor->operation_mem[ ((int *) (bytecode + pc)) [0] ] = StackPop(&processor->stProc);

	                        pc += sizeof(int);

	                        sleep(1);

	                        break;

	                    case MD_POP_IN_RAM_REG:
	                        pc += sizeof(char);

	                        processor->operation_mem[ processor->registers[ ((int *) (bytecode + pc)) [0] - 97 ] ]
	                        = StackPop(&processor->stProc);

	                        pc += sizeof(int);

	                        sleep(1);

	                        break;
	                }
				 } ) // B

DEF_CMD(MUL, 67, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {
            	 	StackPush(&processor->stProc, StackPop(&processor->stProc) * StackPop(&processor->stProc));

               	   	pc += sizeof(char); 
               	 } )  // C

DEF_CMD(ADD, 68, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {
            	 	StackPush(&processor->stProc, StackPop(&processor->stProc) + StackPop(&processor->stProc));

                	pc += sizeof(char);
            	 } ) // D

DEF_CMD(OUT, 69, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {
            	 	printf("%d\n", StackPop(&processor->stProc));

                	pc += sizeof(char);
            	 } ) // E

DEF_CMD(END, 70, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {

            	 } ) // F

DEF_CMD(DIV, 71, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {
            	 	prom = StackPop(&processor->stProc);
                	StackPush(&processor->stProc, StackPop(&processor->stProc) / prom);

                	pc += sizeof(char);
            	 } ) // G

DEF_CMD(SUB, 72, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {
            	 	prom = StackPop(&processor->stProc);
                	StackPush(&processor->stProc, StackPop(&processor->stProc) - prom);

                	pc += sizeof(char);
            	 } ) // H

DEF_CMD(IN, 73, { 
					bytecode[*pc] = numCom;
            	  	*pc += sizeof(char);
            	}, 

            	{
            		printf("Please, enter the number:\n");

                	scanf("%d", &prom);
                	StackPush(&processor->stProc, prom);

                	pc += sizeof(char);
            	} ) // I

DEF_CMD(SQRT, 74, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {
            	 	StackPush(&processor->stProc, ( (int) sqrt(StackPop(&processor->stProc)) ) );

                	pc += sizeof(char);
            	 } ) // J

DEF_CMD(JMP, 75, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	pc += sizeof(char);

                	pc = ((int*) (bytecode + pc)) [0];
				 } ) // K

DEF_CMD(JA, 76, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	prom = StackPop(&processor->stProc);
	                pc += sizeof(char);

	                if (prom > StackPop(&processor->stProc)) {
	                    pc = ((int*) (bytecode + pc)) [0];

	                    break;
	                }

	                pc += sizeof(int);
				 } ) // L Last > pre-Last

DEF_CMD(JB, 77, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	prom = StackPop(&processor->stProc);
                	pc += sizeof(char);

                	if (prom < StackPop(&processor->stProc)) {
                    	pc = ((int*) (bytecode + pc)) [0];

                    	break;
                	}

                	pc += sizeof(int);
				 } ) // M Last < pre-Last

DEF_CMD(JC, 78, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	prom = StackPop(&processor->stProc);
	                pc += sizeof(char);

	                if (prom == StackPop(&processor->stProc)) {
	                    pc = ((int*) (bytecode + pc)) [0];

	                    break;
	                }

	                pc += sizeof(int);
				 } ) // N ==

DEF_CMD(JAC, 79, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	prom = StackPop(&processor->stProc);
	                pc += sizeof(char);

	                if (prom >= StackPop(&processor->stProc)) {
	                    pc = ((int*) (bytecode + pc)) [0];

	                    break;
	                }

	                pc += sizeof(int);
				 } ) // O >=

DEF_CMD(JBC, 80, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	prom = StackPop(&processor->stProc);
	                pc += sizeof(char);

	                if (prom <= StackPop(&processor->stProc)) {
	                    pc = ((int*) (bytecode + pc)) [0];

	                    break;
	                }

	                pc += sizeof(int);
				 } ) // P <=

DEF_CMD(JRC, 81, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	prom = StackPop(&processor->stProc);
	                pc += sizeof(char);

	                if (prom != StackPop(&processor->stProc)) {
	                    pc = ((int*) (bytecode + pc)) [0];

	                    break;
	                }

	                pc += sizeof(int);
				 } ) // Q !=

DEF_CMD(CALL, 82, {
					sscanf(str, "%s :%d", com, &var);
            		bytecode[*pc] = numCom;
            		*pc += sizeof(char);

            		((int*) (bytecode + *pc)) [0] = Ded32[var];
            		*pc += sizeof(int);
				 },

				 {
				 	pc += sizeof(char);

	                callLabels.push(pc + sizeof(int));

	                pc = ((int*) (bytecode + pc)) [0];
				 } ) // R

DEF_CMD(RET, 83, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
            	 },

            	 {
            	 	pc = callLabels.top();
                	callLabels.pop();
            	 } ) // S

DEF_CMD(CAT, 84, {
					bytecode[*pc] = numCom;
            	   	*pc += sizeof(char); 
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

                	pc += sizeof(char);
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


