#include "string_ops.h"
#include "mem_ops.h"

void *entropy_clock(void)
{
	double cpu_time;
	struct timeval tv;

	cpu_time = ((double) clock()) / CLOCKS_PER_SEC;
	gettimeofday(&tv, NULL);
	srandom((getpid() << 16) ^ tv.tv_sec ^ tv.tv_usec ^ (int)cpu_time);
  	return NULL;	
}


char *rand_str(char *dst, int size)
{
	static const char text[] =	"abcdefghijklmnopqrstuvwxyz"                     
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	entropy_clock();

	int i, len = random() % (size - 1);
  
	if( !len ) 
		len=8;
 
	for ( i=0; i<len; ++i )
		dst[i] = text[random() % (sizeof text - 1)];

   	dst[i] = '\0';

	return dst;
}

int char_type_counter(char *string,char type)
{
	int counter=0;
 
	while(*string != '\0')
	{
		if(*string==type) 
			counter++;
		string++;
	}
  
	return counter;
}


void chomp(char * str)
{
 
	while (*str) 
	{
		if ( *str == '\n' || *str == '\r' ) 
		{
			*str = 0;
			return;
		}
		str++;
	}
  
}

char *payload_injector(char * ptr,char * payload,int counter)
{
	char *new=xmalloc((strlen(ptr)+strlen(payload)+2)*sizeof(char));
	short i=0,x=1;
	memset(new, 0,sizeof(char)*(strlen(ptr)+strlen(payload)+1));

	while(*ptr != '\0')
	{
		if(*ptr == '!')
		{
			if(counter==x)
			{
				strncat(new,payload,strlen(payload));
				i+=strlen(payload);
			}
			x++;
		} 
		else 
		{ 
			*(new+i)=*ptr;
			i++;
		}
		ptr++;
	}

	return new;
}


int 
strstr_regex(char *string, char *expression)
{

	regex_t regex;
	int reti;

// Compile regular expression
	reti = regcomp(&regex, expression, 0);

	if(reti) 
		DEBUG("Could not compile regex ! \n");

	reti = regexec(&regex, string, 0, NULL, 0);

	regfree(&regex);
  
	if( !reti )
		return 1;
	else 
		return 0;

}


