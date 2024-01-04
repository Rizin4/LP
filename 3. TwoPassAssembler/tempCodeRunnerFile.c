sprintf(a,"%x",atoi(operand));
			fprintf(fp5,"%s\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,a);
			
			fprintf(fp6,"^00000%s",a);