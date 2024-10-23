//gcc sweet_game.c -o sweet_game -Wl,-z,relro,-z,now -lseccomp -s

#include <time.h>
#include <fcntl.h>
#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <unistd.h>

void welcome(){

    printf("  A   L     I  EEEE  N   N    GGG   A   M   M EEEE\n");
    printf(" A A  L     I  E     NN  N   G   G A A  MM MM E   \n");
    printf("AAAAA L     I  EEEE  N N N  G     AAAAA M M M EEEE\n");
    printf("A   A L     I  E     N  NN   G  GG A   A M   M E   \n");
    printf("A   A LLLLL I  EEEE  N   N    GGG  A   A M   M EEEE           v0.1\n");
    fflush(stdout);
}

int game(){
	int guess;
	int magic;
	char *greetings[] = {
    "1: Reach for the stars; you might just catch one!",
    "2: Ignite the cosmic flame within you!",
    "3: Celestial traveler, let's have some interstellar fun!",
    "4: Ready to embark on an astronomical journey?",
    "5: Buckle up, it's time for a cosmic adventure!",
    "6: You're about to enter a universe of possibilities.",
    "7: Get ready for an amazing celestial experience!",
    "8: Welcome, let's launch this cosmic party!",
    "9: Exciting times await in the vast cosmos, welcome aboard!",
    "10: Your journey through the galaxies begins now!",
    "11: Step into the cosmos of possibilities.",
    "12: Join the cosmic fun and enjoy the interstellar ride!",
    "13: The journey to the stars begins with you!",
    "14: Prepare for a fantastic astral experience.",
    "15: Welcome to the universe of endless possibilities.",
    "16: The cosmic stage is yours, shine like a supernova!",
    "17: Time to shine bright like distant stars and have some fun!",
    "18: Embrace the astronomical adventure that lies ahead.",
    "19: You're in for a celestial treat!",
    "20: The cosmic fun starts now!",
	};
	
	printf("\nGuess the next alien quote number.\nChoose a number from 1 to 20:");
  	fflush(stdout);
	scanf("%d",&guess);
    if ((guess < 1) || (20 < guess)) {
    	puts("Invalid value!");
    	return 0;
    }
    magic = (rand() + 8)%20 + 1;
	printf("\nQuote | %s\n",greetings[magic]);

	if (guess != magic){
		puts("\nYou lost.");
		return 0;
		}
	puts("\nYou win.");
	return 1;
}
void sandbox() {
  scmp_filter_ctx ctx;
  ctx = seccomp_init(SCMP_ACT_ALLOW);
  if (ctx == NULL) {
    exit(0);
  }
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(open), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execveat), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(write), 0);

  seccomp_load(ctx);
}
void sweetttttttttt(){
	void *shellcode = mmap(0, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC,
		                 MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	void (*sc)();

	memset(shellcode, 0, 0x1000);
	fflush(stdout);
	printf("Give us your feedbacks for this game: ");
	fflush(stdout);
	read(0, shellcode, 605);

	sandbox();

	sc = (void *)shellcode;
	sc();

}


int main(){

	char name[10];
	time_t seed;
	long secret;
	
	seed = time(0);
	
	welcome();
	printf("\nEnter your name to access the system: ");
	fflush(stdout);
	read(0,name,0x50);
	printf("\nWelcome Alien %s\nEnter the secret code to proceed: ",name);
	fflush(stdout);
	scanf("%s",&secret);

	srand(seed);
	
	if(secret * 0x636172696e6165u == 0x51a6f0882ada4029u){
		puts("\nCorrect Secret code..");
		puts("Welcome in the game space.\n");
		for(int i=0; i<70;i++){
			if (!game()){
				puts("Bye bye!");
				return 0;}
		}
		sweetttttttttt();

	}
	else
		puts("\nWrong Secret ..!");
}
