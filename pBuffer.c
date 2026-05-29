#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void ) {

    void *pBuffer = malloc(500);

    if ( !pBuffer ) {
        printf( "Memory error." );
        return 1;
    }

    int *op = ( int * )pBuffer;
    int *i = ( int * )( ( char * )pBuffer + sizeof( int ) );
    int *currentSize = ( int * )( ( char * )pBuffer + ( 2 * sizeof( int ) ) );
    char *flag = ( char * )pBuffer + ( 3 * sizeof(int) );
    char *stringScan = ( char * )pBuffer + ( 3 * sizeof(int) ) + sizeof( char );
    char *stringStore = ( char * )pBuffer + 250;

    *i = 0;
    *currentSize = 500;

    while ( 1 ) {
    printf( "\nMENU - Choose an option:\n" );
		printf( "\t1. Add person\n" );
		printf( "\t2. Remove person\n" );
		printf( "\t3. Search person\n" );
		printf( "\t4. List\n" );
		printf( "\t5. Exit\n" );
		scanf( "%d", op );

        switch ( *op ) {
            case 1: { // Add person
                if ( ( ( char * )pBuffer + *currentSize ) - stringStore < 250 ) {
                    void *oldStart = pBuffer;
                    *currentSize += 500;
                    
                    void *temp = realloc( pBuffer, *currentSize );
                    if ( !temp ) {
                        printf( "Realloc error.\n" );
                        break; 
                    }
                    
                    pBuffer = temp;
                    stringStore = ( char * )pBuffer + ( stringStore - ( char * )oldStart );
                    op = ( int * )pBuffer;
                    i = ( int * )( ( char * )pBuffer + sizeof( int ) );
                    currentSize = ( int * )( ( char * )pBuffer + ( 2 * sizeof( int ) ) );
                    flag = ( char * )pBuffer + ( 3 * sizeof( int ) );
                    stringScan = ( char * )pBuffer + ( 3 * sizeof( int ) ) + 1;
                }

                printf( "Name: " );
                scanf( " %99[^\n]", stringScan );
                strcpy( stringStore, stringScan );
                stringStore += strlen( stringStore ) + 1;

                printf( "Age: " );
                scanf( "%d", (int *)stringStore );
                stringStore += sizeof( int );

                printf( "E-mail: " );
                scanf( " %99[^\n]", stringScan );
                strcpy( stringStore, stringScan );
                stringStore += strlen( stringStore ) + 1;

                (*i)++;
                break;
            }

            case 2: { // Remove person
                if ( *i == 0 ) {
                    printf( "\nEmpty list.\n" );
                    break;
                }

                printf( "Enter the name to remove: " );
                scanf( " %99[^\n]", stringScan );

                *flag = 0;
                char *navigating = ( char * )pBuffer + 250;
                char *recordStart = 0;

                while ( navigating < stringStore ) {
                    if ( strcmp( navigating, stringScan ) == 0 ) {
                        recordStart = navigating;
                        *flag = 1;
                        
                        while ( *navigating ) {
                            navigating++;
                        }
                        navigating++; 
                        navigating += sizeof( int );
                        while ( *navigating ) {
                            navigating++;
                        }
                        navigating++; 

                        break;
                    }

                    while ( *navigating ) {
                        navigating++;
                    }
                    navigating++;

                    navigating += sizeof(int);

                    while ( *navigating ) {
                        navigating++;
                    }
                    navigating++;
                }

                if ( !*flag ) {
                    printf( "\nPerson not found.\n" );
                } else {
                    memmove( recordStart, navigating, stringStore - navigating );

                    stringStore -= ( navigating - recordStart );
                    (*i)--;
                    printf("\nPerson removed.\n");
                }
                break;
            }

            case 3: { // Search person
                if ( *i == 0 ) {
                    printf( "\nEmpty list.\n" );
                    break;
                }

                printf( "Enter the name to search: " );
                scanf( " %99[^\n]", stringScan );

                *flag = 0;
                char *navigating = ( char * )pBuffer + 250;

                while ( navigating < stringStore ) {
                    if ( strcmp( navigating, stringScan ) == 0 ) {
                        printf( "\nPerson found:\n" );
                        printf( "Name: %s\n", navigating );

                        while ( *navigating ) {
                            navigating++;
                        }
                        navigating++;

                        printf( "Age: %d\n", *(int *)navigating );
                        navigating += sizeof(int);

                        printf( "E-mail: %s\n", navigating );
                        
                        *flag = 1;
                        break; 
                    }
                    
                    while ( *navigating ) { 
                        navigating++;
                    }
                    navigating++;
                    navigating += sizeof( int );
                    while ( *navigating ) {
                        navigating++;
                    }
                    navigating++;
                }

                if ( !*flag ) {
                    printf( "\nPerson not found.\n" );
                }
                break;
            }

            case 4: { // List
                if ( *i == 0 ) {
                    printf( "Empty list.\n" );
                    break;
                }

                char *navigating = ( char * )pBuffer + 250;

                while ( navigating < stringStore ) {
                    printf( "\nName: %s\n", navigating );
                    while ( *navigating ) {
                        navigating++;
                    }
                    navigating++;

                    int *agePtr = ( int * )navigating;
                    printf( "Age: %d\n", *agePtr );
                    navigating += sizeof( int );

                    printf( "E-mail: %s\n", navigating );
                    while ( *navigating ) {
                        navigating++;
                    }
                    navigating++;
                }
                break;
            }

            case 5: // Exit
                free( pBuffer );
                exit( 0 );
                break;

            default:
                break;
        }
    }
}
