/*
*  kernel.c
*/
<<<<<<< HEAD

=======
>>>>>>> 527ef2042d228fe327b0ee18aacee8f5803b19bf

void kernel(void)
{
	init_syscalls(); // ecrase interruption 80 pour la notre
        //char *myString = "hello\0";
	interrupt(0x80,1,"costa rica ticos",0,0);
	while(1); // évite d'aller lire plus loin
}
