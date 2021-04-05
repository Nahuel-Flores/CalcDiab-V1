#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

typedef struct
{
int legajo;
char usuario[30];
char contrasenia[12];
int anioNaci;
char genero;        //m o f
int contHDC;        //Contador de hidratos de carbono
}usuario;

typedef struct
{
int medicion;       //Parametro de medicion
int dosis;          //Parametro de cant de u de insulina
}parametros;

typedef struct
{
char alimento[50];
float porcion;
float HDC;      //Cant de HDC
}alimentos;

void imprimirCabecera(char cabecera[10]);
void opciones();
void opciones2();
void menu();
void menuDiabe(usuario usu);
void menu_inicio_de_sesion();
void cargarAlimentos(char nombreArchi[]);
void cargarParametros(char nombreArchi[]);
void mostrarAlimentos(char nombreArchi[]);

usuario registrarse(char nombreArchi[]);
usuario ingreso(char nombreArchi[]);
usuario buscarEstructdUsuario(char nombreArchi[],char nombreU[]);

int validacion(char nombreArchi[],usuario u);
int cantArchivos(char nombreArchi[],int pesoE);
int calculoMedicion(char nombreArchi[],int medicion);
int alimentosIngeridos(char nombreArchi[],int contHdc);
int sumaHidratos(char nombreArchi[],Pila posiciones);
int buscarUsuario(char nombreArchi[], char nombreU[]);

void bye();

int main()
{
    system("COLOR 61");
    menu();
    return 0;
}

void menu(){        //Menu Principal

    int num;
    int error = 0;
    usuario usuar;
    imprimirCabecera("CalcDiab");
    opciones();
    printf("\n\n\n\t\t\t ");

    do{
        fflush(stdin);
        scanf("%d", &num);

        switch (num){
        case 1:
            usuar = ingreso("ListaDeUsuarios");
            menuDiabe(usuar);
        break;

        case 2:
            usuar = registrarse("ListaDeUsuarios");
            cargarParametros(usuar.usuario);
            menuDiabe(usuar);
        break;

        case 0:
            system("cls");
            bye();
        break;

        default:
            printf("\nNo es una opcion valida.Continuar...\n");
            system("pause");
            error = 1;
        break;
        }
    }
    while(error==1);
    }

void menuDiabe(usuario usu){    //Segundo menu
    int num,medi,inyec;
    int error = 0;
    usu.usuario[0] = toupper(usu.usuario[0]);

    do{
    system("cls");
    imprimirCabecera(usu.usuario);
    opciones2();
    printf("\n\n\n\t\t\t ");
    fflush(stdin);
    scanf("%d", &num);
        switch(num){
    case 1:
        system("cls");
        imprimirCabecera(usu.usuario);
        printf("\nIngrese su valor de glucosa en sangre: ");
        scanf("%i",&medi);

        inyec = calculoMedicion(usu.usuario,medi);

        printf("\n\n\tDebe inyectarse: %i u\n\n",inyec);

        break;
    case 2:
        system("cls");
        imprimirCabecera(usu.usuario);
        inyec = alimentosIngeridos("ListaDeAlimentos",usu.contHDC);

        printf("\n\n\tDebe inyectarse: %i u\n\n",inyec);
        break;
    case 3:
        system("cls");
        imprimirCabecera(usu.usuario);
        printf("\nIngrese su valor de glucosa en sangre: ");
        scanf("%i",&medi);

        inyec = calculoMedicion(usu.usuario,medi);

        inyec = inyec + alimentosIngeridos("ListaDeAlimentos",usu.contHDC);

        printf("\n\n\tDebe inyectarse: %i u\n\n",inyec);
        break;
    case 4:
        system("cls");
        mostrarAlimentos("ListaDeAlimentos");
        cargarAlimentos("ListaDeAlimentos");
        break;
    case 0:
        bye();
        break;
    default:
        printf("\nNo es una opcion valida.Continuar...\n");
        system("pause");
        break;
        }
        if(num != 0)
            system("pause");

    }while(num != 0);
}

void imprimirCabecera(char cabecera[10]){   //Imprime la cabecera dentro de un recuadro
    int i;
    printf("%c", 201);
    for(i=0;i<50;i++){
        printf("%c",205);
    }
    printf("%c\n", 187);
    printf("%c%32s%19c\n", 186,cabecera,186);
    printf("%c", 200);
    for(i=0;i<50;i++){
        printf("%c",205);
    }
    printf("%c", 188);
}

void opciones(){    //Muestra las opciones del menu 1
    printf("\n\n\t");
    for(int i=0;i<33;i++){
        printf("%c", 219);
    }
    printf("\n\t%c\t\t\t\t%c", 219, 219);
    printf("\n\t%c\t(1) Iniciar sesion\t%c",219 , 219);
    printf("\n\t%c\t\t\t\t%c", 219, 219);
    printf("\n\t%c\t  (2) Registrarse\t%c", 219, 219);
    printf("\n\t%c\t\t\t\t%c", 219, 219);
    printf("\n\t%c\t    (0) Salir\t\t%c", 219, 219);
    printf("\n\t%c\t\t\t\t%c\n\t", 219, 219);
    for(int i=0;i<33;i++){
        printf("%c", 219);
    }
}

void opciones2(){   //Muestra las opciones del menu 2
    printf("\n\n\t");
    for(int i=0;i<33;i++){
        printf("%c", 219);
    }
    printf("\n\t%c\t\t\t\t%c", 219, 219);
    printf("\n\t%c   (1) Medida a inyectarse\t%c",219 , 219);
    printf("\n\t%c     segun glucosa en sangre\t%c", 219, 219);
    printf("\n\t%c\t\t\t\t%c", 219, 219);
    printf("\n\t%c   (2) Medida a inyectarse\t%c", 219, 219);
    printf("\n\t%c     segun ingesta\t\t%c", 219, 219);
    printf("\n\t%c\t\t\t\t%c", 219, 219);
    printf("\n\t%c   (3) Calcular ambos\t\t%c", 219, 219);
    printf("\n\t%c\t\t\t\t%c\t", 219, 219);
    printf("\n\t%c   (4) Ingresar alimento\t%c", 219, 219);
    printf("\n\t%c\t\t\t\t%c", 219, 219);
    printf("\n\t%c\t    (0) Salir\t\t%c", 219, 219);
    printf("\n\t%c\t\t\t\t%c\n\t", 219, 219);
    for(int i=0;i<33;i++){
        printf("%c", 219);
    }
}

usuario registrarse(char nombreArchi[]){   //Registrarse
    FILE*archi;
    int id;
    int cmp = 0;
    int busca = 0;
    char verif[12];
    usuario u;

    archi = fopen(nombreArchi,"ab");

    if(archi != NULL){

        id = cantArchivos(nombreArchi,sizeof(usuario)) + 1;

        u.legajo = id;

        do{
            system("cls");
            imprimirCabecera("Registro");
            if(busca == 1)
                printf("\n\n\tEl usuario ya existe. Vuelva a ingresar");

            printf("\n\n\t\tUsuario: ");
            scanf("%s",&u.usuario);

            busca = buscarUsuario(nombreArchi,u.usuario);
        }
        while(busca == 1 );

        do{
            system("cls");
            imprimirCabecera("Registro");
                        if(cmp != 0)
                printf("\n\n\tLas contasenias no coinciden. Vuelva a ingresar");

            printf("\n\n\t%c%c\t\t\t       %c%c", 219, 219, 219, 219);
            printf("\n\t%c\t\t\t\t%c\n\t", 219, 219);

            printf("\n\t\tUsuario: %s\n", u.usuario);

            printf("\n\t   Contrasenia:");
            fflush(stdin);
            scanf("%s", &u.contrasenia);
            printf("\n\t   Repita la contrasena:");
            fflush(stdin);
            scanf("%s", &verif);
            printf("\n\t%c\t\t\t\t%c\n", 219, 219);
            printf("\t%c%c\t\t\t       %c%c", 219, 219, 219, 219);


            cmp = strcmp(u.contrasenia,verif);
        }
        while(cmp != 0);

        printf("\n\n\tIngresar anio de nacimiento: ");
        fflush(stdin);
        scanf("%i",&u.anioNaci);


        printf("\n\tIngresar genero(m/f): ");
        fflush(stdin);
        scanf("%c",&u.genero);

        while(u.genero != 'm' && u.genero != 'f'){
            printf("\n\tGenero incorrecto. Vuelve a ingresar genero: ");
            fflush(stdin);
            scanf("%c",&u.genero);
            }

        printf("\n\tIngrese cant de Hidratos de carbono\n\tpor los que se inyecta 1 u de insulina: ");
        scanf("%i",&u.contHDC);

        fwrite(&u,sizeof(usuario),1,archi);

        system("cls");

        fclose(archi);
  }

return u;
}

usuario ingreso(char nombreArchi[]){       //Inicio de sesion

    usuario u;
    usuario usufin;
    int ing = -1;

    char incripcion;

    while(ing != 2){

        system("cls");
        imprimirCabecera("Inicio de sesion");
        if(ing != -1)
            printf("\n\tUsusuario/Contraseña incorrectos\n");

            printf("\n\t%c%c\t\t\t       %c%c", 219, 219, 219, 219);
            printf("\n\t%c\t\t\t\t%c\n\t", 219, 219);
            printf("\n\t\tUsuario: ");
            fflush(stdin);
            scanf("%s", &u.usuario);
            printf("\n\t\tContrasena: ");
            fflush(stdin);
            scanf("%s", &u.contrasenia);
            printf("\n\t%c\t\t\t\t%c\n", 219, 219);
            printf("\t%c%c\t\t\t       %c%c", 219, 219, 219, 219);

        ing = validacion(nombreArchi,u);
    }

    usufin = buscarEstructdUsuario(nombreArchi,u.usuario);

return usufin;
}

usuario buscarEstructdUsuario(char nombreArchi[],char nombreU[]){       //Buscar un usuario y retornarlo su estructura de tipo usuario

    FILE*archi;

    usuario usu;
    int flag = 0;
    int cmp;

    archi = fopen(nombreArchi,"rb");

    if(archi != NULL){

        while(fread(&usu,sizeof(usuario),1,archi) > 0 && flag == 0){

            cmp = strcmpi(nombreU,usu.usuario);

            if(cmp == 0)
                flag = 1;

        }
    fclose(archi);

    return usu;
    }
}

int validacion(char nombreArchi[],usuario u){      //Valida el usuario y la contraseña

    FILE *archi;

    usuario veriU;
    int flag = 0;

    archi = fopen(nombreArchi,"rb");

    if(archi != NULL){

        while(fread(&veriU,sizeof(usuario),1,archi) > 0 && flag == 0){

            if(strcmpi(u.usuario,veriU.usuario) == 0)
                flag = 1;   //Usuario validado

        }

        if (flag == 1){

            if(strcmpi(u.contrasenia,veriU.contrasenia) == 0)
                flag = 2;   //Usuario y contraseña validados
                        }

        fclose(archi);
  }

return flag;    //Valores posibles 0(no existe el usuari),1(contraseña incorrecta) y 2(Ingreso con exito)
}

int cantArchivos(char nombreArchi[],int pesoE){   //Se necesita pasr el peso de la estructura que posee el archivo y retorna la cantidad de archivos

    FILE *archi;
    int cant;

    archi = fopen(nombreArchi,"rb");

    if(archi != NULL){

        fseek(archi,0,SEEK_END);
        cant = ftell(archi)/pesoE;

        fclose(archi);
        }
    else
        cant = 0;

return cant;
 }

 void cargarAlimentos(char nombreArchi[]){      //Carga ARCHIVO de estura Alimentos

    FILE*archi;

    char salida;
    alimentos a;

    archi = fopen(nombreArchi,"ab");

    if(archi != NULL){
        do{
            printf("Ingresar Alimento: ");
            scanf("%s",&a.alimento);

            a.alimento [0] = toupper (a.alimento [0]);

            printf("\nIngresar cant de la porcion: ");
            fflush(stdin);
            scanf("%f",&a.porcion);

            printf("\nIngresar hidratos de carbono que posee: ");
            scanf("%f",&a.HDC);

            printf("\n\tPresiona ESC si deseas dejar de cargar alimentos");
            salida = getch();

            fwrite(&a,sizeof(alimentos),1,archi);

            system("cls");
        }
        while(salida != 27);

        fclose(archi);
    }
 }

 void cargarParametros(char nombreArchi[]){     //Carga ARCHIVO de estura Parametros

    FILE*archi;

    char salida;
    int i = 1;
    parametros p;

    archi = fopen(nombreArchi,"ab");

    if(archi != NULL){

        do{
            printf("Ingresar valor a partir del que se inyecta %i u de insulina : ",i);
            scanf("%i",&p.medicion);

            p.dosis = i;

            i++;
            printf("\n\tPresione ESC si desea dejar de cargar parametros");
            salida = getch();

            fwrite(&p,sizeof(parametros),1,archi);

            system("cls");
        }
        while(salida != 27);

        fclose(archi);
    }
 }

 int calculoMedicion(char nombreArchi[],int medicion){   //Calcula la cantidad de dosis que se deben aplicar segun el azucar en sangre

    FILE*archi;

    int dosis = -1;
    parametros compP;

    archi = fopen(nombreArchi,"rb");

    if(archi != NULL){

        while(fread(&compP,sizeof(parametros),1,archi) > 0 && dosis == -1){

            if(compP.medicion > medicion)
                dosis = compP.dosis -1;
        }

        if(dosis == -1){            //Por si la medidion es mas grande que los parametros pone el valor maximo que se inyecta

        fseek(archi,0,SEEK_END);
        fread(&compP,sizeof(parametros),1,archi);
        dosis = compP.dosis;
        }

    fclose(archi);
    }


return dosis;
 }

int alimentosIngeridos(char nombreArchi[],int contHdc){  //Muestra los alimentos pide que se ingrese cuales comio y calcula en base a eso
    Pila a1;
    inicpila(&a1);

    int inyec;
    char salida;

    int ali;

    do{
        system("cls");

        mostrarAlimentos(nombreArchi);

        printf("\nIngrese el numero correspondiente al alimento  que consumio: ");
        scanf("%i", &ali);
        apilar(&a1,ali);

        printf("\n\tPresione ESC si desea dejar de cargar alimentos");
        salida = getch();
    }
    while(salida != 27);

    inyec = calcHidratos(nombreArchi,a1,contHdc);

 return inyec;
}

int calcHidratos(char nombreArchi[],Pila posiciones,int contHdc){   //Calcula la cantidad de ml de insulina que hay que inyectarse segun lo que comio

    FILE *archi;

    int hdc = 0;
    int posAl,inyec;

    alimentos a;

    archi = fopen(nombreArchi,"rb");

    if(archi != NULL){

        while(!pilavacia(&posiciones)){

            posAl = tope(&posiciones);
            desapilar(&posiciones);

            fseek(archi,(posAl-1)*sizeof(alimentos),SEEK_SET);
            fread(&a,sizeof(alimentos),1,archi);

            hdc = a.HDC + hdc;
        }

        fclose(archi);
    }

    inyec = hdc/contHdc;

return inyec;
}

void mostrarAlimentos(char nombreArchi[]){  //Muestra la lista de los alimentos
    FILE *archi;
    alimentos alim;
    int i = 1;

    archi = fopen(nombreArchi, "rb");

    if(archi != NULL){
        imprimirCabecera("Lista de alimentos");
        puts("\n--------------");
        while(fread(&alim, sizeof(alimentos), 1, archi) > 0){

            printf("\n %i) %s\t  %.1f g/ml/u", i, alim.alimento, alim.porcion);
            i++;
        }
        puts("\n\n--------------\n\n");
        fclose(archi);
            }

}

int buscarUsuario(char nombreArchi[],char nombreU[]){       //Buscar un usuario y retorna 1 si existe o 0 si no existe en el archivo
    FILE*archi;

    usuario usu;
    int flag = 0;
    int cmp;

    archi = fopen(nombreArchi,"rb");

    if(archi != NULL){

        while(fread(&usu,sizeof(usuario),1,archi) > 0 && flag == 0){

            cmp = strcmpi(nombreU,usu.usuario);

            if(cmp == 0)
                flag = 1;

        }
    fclose(archi);

    return flag;
    }
}

void bye(){     //Muestra el mensaje de salida
    system("cls");
    printf("\n\n\n%c%c%c%c%c%c%c%c\t%c%c%c%c\t    \t%c%c%c%c    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c%c%c%c%c\t%c%c%c%c\t    \t%c%c%c%c    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c\t%c%c%c%c\t    %c%c%c%c    %c%c%c%c\t%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c\t%c%c%c%c\t    %c%c%c%c    %c%c%c%c\t%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c\t\t%c%c%c%c\t\t%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c\t\t%c%c%c%c\t\t%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c\t    %c%c%c%c\t%c%c%c%c\t\t%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c\t    %c%c%c%c\t%c%c%c%c\t\t%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c\t    %c%c%c%c\t%c%c%c%c\t\t%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c\t    %c%c%c%c\t%c%c%c%c\t\t%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c\t\t%c%c%c%c\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c\t\t%c%c%c%c\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\n\n\n");
}
