
void *busquedaBinaria(const void *clave, const void *base, size_t ce, size_t tam, int(*cmp)(const void *d1, const void *d2))
{
    int li, ls, pm, comp;
    li = 0;
    ls = ce - 1;

    while(li <= ls)
    {
        pm = (li +ls) / 2;
        comp = cmp(base + (pm * tam), clave);

        if(comp == 0)
            return (void*)(base + (pm * tam));
        if(comp > 0)
            ls = pm -1;
        if(comp < 0)
            li = pm + 1;
    }

    return NULL;
}

void * buscarMenor(const void * vec,
                   const void * fin,
                   size_t tam,
                   int (*cmp)(const void*, const void*));

void * orenarSeleccion(void * vec,
                     size_t ce,
                     size_t tam,
                     int (*cmp)(const void*, const void*))
{
    void * ini = vec,
         * fin = vec + (ce - 1) * tam,
         * men;

    while(vec < fin)
    {
        men = buscarMenor(vec, fin, tam, cmp);
        if (vec!=men)
        {
            intercambiar(vec, men, tam);
        }
        vec+=tam;
    }
    return ini;
}
/// >0 1ero mayor
/// <0 1ero menor
/// =0 iguales

void * buscarMenor(const void * vec,
                   const void * fin,
                   size_t tam,
                   int (*cmp)(const void*, const void*)
                   )
{
    const void * men = vec;
    vec+=tam;

    while(vec <= fin)
    {
        if (cmp(vec, men)<0)
        {
            men = vec;
        }
        vec+=tam;
    }
    return (void *) men;
}



void intercambiar(void * e1, void * e2, size_t tam)
{
    void * aux = malloc(tam);
    if (!aux)
        return;

    memcpy(aux, e1, tam);
    memcpy(e1, e2, tam);
    memcpy(e2, aux, tam);

    free(aux);
}


///Archivos
void actualizar(const void* nombreTxt, const void* nombreBin)
{
    FILE *archEst, *archEmp;
    Estudiante est;
    Empleado emp;
    int i, cmp;


    archEst = fopen(nombreTxt, "rt");
    archEmp = fopen(nombreBin, "r+b");

    if(!archEst || !archEmp)
    {
        fclose(archEst);
        fclose(archEmp);
        return;
    }

    fread(&emp, sizeof(Empleado), 1, archEmp);
    i = fscanf(archEst,"%d|%[^|\n]|%[^|\n]|%f\n", &est.dni, est.apellido, est.nombre, &est.promedio);

    while(!feof(archEmp) && i != EOF)
    {
        cmp = emp.dni - est.dni;
        if(cmp < 0)
            fread(&emp, sizeof(Empleado), 1, archEmp);
        else if(cmp > 0)
            i = fscanf(archEst,"%d|%[^|\n]|%[^|\n]|%f\n", &est.dni, est.apellido, est.nombre, &est.promedio);
        else
        {
            if(est.promedio >= 7)
            {
                emp.sueldo *= 1.0728;
                fseek(archEmp, (int)sizeof(Empleado) *-1, SEEK_CUR);
                fwrite(&emp, sizeof(Empleado), 1, archEmp);
                fseek(archEmp, 0L, SEEK_CUR);
            }
            fread(&emp, sizeof(Empleado), 1, archEmp);
            i = fscanf(archEst,"%d|%[^|\n]|%[^|\n]|%f\n", &est.dni, est.apellido, est.nombre, &est.promedio);
        }
    }
    fclose(archEst);
    fclose(archEmp);
}


int crearLoteEst(const void* nombreTxt)
{
    FILE *archEst;
    int i;
    Estudiante vEst[]=
    {
        {123, "Lopez", "Juan", 7},
        {234, "Rodriguez", "Ana", 5},
        {345, "Sanchez", "Carlos", 2},
        {432, "Ramirez", "Mariana", 10},
        {567, "Gonzalez", "Pedro", 8},
        {789, "Perez", "Luis", 6},
        {890, "Martinez", "Laura", 9},
        {901, "Torres", "Diego", 8},
    };

    archEst = fopen(nombreTxt, "wt");
    if(!archEst)
        return -10;

    for(i = 0; i < 8; i++)
        fprintf(archEst, "%d|%s|%s|%f\n", vEst[i].dni, vEst[i].apellido, vEst[i].nombre, vEst[i].promedio);

    fclose(archEst);

    return 1;
}


int crearLoteEmp(const void* nombreBin)
{
    FILE *archEmp;
    Empleado vEmp[] =
    {
        {123, "Lopez", "Juan", 2500.0},
        {234, "Rodriguez", "Ana", 4000.0},
        {345, "Sanchez", "Carlos", 2200.0},
        {456, "Gomez", "Maria", 3200.0},
        {567, "Gonzalez", "Pedro", 3100.0},
        {678, "Fernandez", "Sofia", 2700.0},
        {789, "Perez", "Luis", 1800.0},
        {901, "Torres", "Diego", 3500.0},
    };
    archEmp = fopen(nombreBin, "wb");
    if(!archEmp)
        return -10;
    fwrite(vEmp, sizeof(Empleado), sizeof(vEmp) / sizeof(*vEmp), archEmp);
    fclose(archEmp);
    return 1;
}


void trozarArchFijo(void *dato, char *cad)
{
    Alumno *alu = (Alumno*)dato;
    char *aux = cad;

    while(*aux)
        aux++;

    *aux = '\0';

    aux -= 6;
    sscanf(aux, "%f", &(alu->nota));
    *aux = '\0';

    aux -= 29;
    strcpy(alu->nombre, aux);
    *aux = '\0';

    sscanf(cad, "%d", &(alu->dni));

}
void trozarEmpleado(char *cad, Empleado *emp)
{
    char *aux = strchr(cad, '\n');
    *aux = '\0';

    aux = strrchr(cad, '|');
    sscanf(aux + 1, "%f", &emp->sueldo);
    *aux = '\0';

    aux = strrchr(cad, '|');
    sscanf(aux + 1, "%c", &emp->sexo);
    *aux = '\0';

    aux = strrchr(cad, '|');
    strcpy(emp->apellido, aux + 1);
    *aux = '\0';

    aux = strrchr(cad, '|');
    strcpy(emp->nombre, aux + 1);
    *aux = '\0';

    sscanf(cad, "%d", &emp->dni);

}

void *rBinaria(int li, int ls, size_t tam, const void *clave, const void *base, int(*cmp)(const void *d1, const void *d2))
{
    int pm, comp;

    pm = (li + ls) / 2;
    comp = cmp(base + (pm * tam), clave);

    if(li > ls)
        return NULL;


    if(comp == 0)
        return (void*)(base + (pm * tam));
    if(comp > 0)
        return rBinaria(li, pm - 1, tam, clave, base, cmp);
    if(comp < 0)
        return rBinaria(pm + 1, ls, tam, clave, base, cmp);

    return NULL;
}

void *busquedaBinaria(const void *clave, const void *base, size_t ce, size_t tam, int(*cmp)(const void *d1, const void *d2))
{
    int li, ls;
    li = 0;
    ls = ce - 1;

    return rBinaria(li, ls, tam, clave, base, cmp);
}

///Arbol IDX


#define MIN(X, Y)   ((X > Y) ? (Y) : (X))


tArbolBinBusq* buscar_nodo_no_clave(const tArbolBinBusq* pa, void* pd,
                                          int (*cmp)(const void *, const void *))
{
    const tArbolBinBusq* res;

    if(!*pa)
        return NULL;

    if(cmp(pd, (*pa)->info) == 0)
        return (tArbolBinBusq*)pa;

    if((res = buscar_nodo_no_clave(&(*pa)->izq, pd, cmp)))
       return (tArbolBinBusq*)res;

    return buscar_nodo_no_clave(&(*pa)->der, pd, cmp);
}

int buscarElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *))
{
    const tArbolBinBusq* elem;

    if(!*p)
        return SIN_INICIALIZAR;

    elem = buscar_nodo_no_clave(p, d, cmp);

    memcpy(d, (*elem)->info, MIN((*elem)->tamInfo, tam));

    return TODO_OK;
}

tNodoArbol** mayor_nodo_arbol( tArbolBinBusq* pa)
{
    while(*pa && (*pa)->der)
        pa = &(*pa)->der;

    return pa;
}

tNodoArbol** menor_nodo_arbol( tArbolBinBusq* pa)
{
    while(*pa && (*pa)->izq)
        pa = &(*pa)->izq;

    return pa;
}

unsigned alturaArbolBin(const tArbolBinBusq *p)
{
    int hi, hd;

    if(!*p)
        return 0;

    hi = alturaArbolBin(&(*p)->izq);
    hd = alturaArbolBin(&(*p)->der);

    return hi > hd ? hi + 1 : hd + 1;
}

int eliminarRaizArbolBinBusq(tArbolBinBusq *p)
{
    tNodoArbol** remp, *elim;

    if(!*p)
        return SIN_INICIALIZAR;

    free((*p)->info);

    if(!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p = NULL;
        return TODO_OK;
    }

    remp =  alturaArbolBin(&(*p)->izq) > alturaArbolBin(&(*p)->der) ?
            mayor_nodo_arbol(&(*p)->izq) :
            menor_nodo_arbol(&(*p)->der);

    elim = *remp;

    (*p)->info = elim->info;
    (*p)->tamInfo = elim->tamInfo;

    *remp = elim->izq ? elim->izq : elim->der;

    free(elim);

    return TODO_OK;
}


void eliminarElemNoClaveArbol(tArbolBinBusq *p, void *d,
                             int (*cmp)(const void *, const void *))
{
    if(!(p = buscar_nodo_no_clave(p, d, cmp)))
        return;

    memcpy(d, (*p)->info, (*p)->tamInfo);

    eliminarRaizArbolBinBusq(p);
}

//**************************************************************************************************************

void grabar_archivo(void* elem, unsigned n, void* params)
{
    FILE* pf = (FILE*)params;
    tRegInd* idx = (tRegInd*)elem;

    fwrite(idx, sizeof(tRegInd), 1, pf);
}

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                                       void (*accion)(void *, unsigned, void *))
{
    if(!*p)
        return;

    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->izq, params, grabar_archivo);
    accion((*p)->info, 0, params);
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->der, params, grabar_archivo);
}

int grabarEnArchivoOrdenadoArbolBin(tArbolBinBusq *p, const char * path)
{
    FILE* pf = fopen(path , "wb");

    if(!pf)
    {
        printf("\nERROR AL GRABAR EL ARCHIVO %s\n", path);
        return ERROR_ARCHIVO;
    }

    if(!*p)
        return SIN_INICIALIZAR;

    recorrerEnOrdenSimpleArbolBinBusq(p, pf, grabar_archivo);

    return TODO_OK;
}

//**************************************************************************************************************

void podar_arbol(tArbolBinBusq *pa)
{
    if(!*pa)
        return;

    if(!(*pa)->der && !(*pa)->izq)
    {
        free((*pa)->info);
        free(*pa);
        *pa = NULL;
        return;
    }

    podar_arbol(&(*pa)->izq);
    podar_arbol(&(*pa)->der);
}

void vaciarArbolBin(tArbolBinBusq *p)
{
    while(*p)
        podar_arbol(p);
}


int es_arbol_vacio(tArbolBinBusq *p)
{
    return *p == NULL;
}


///Arbol
int arbolBalanceado(const Arbol *pa)
{
    int h = alturaArbol(pa);

    if(h <= 2)
        return 1;

    return arbolCompletoHastaNivel(pa, h - 2);
}

int eliminarNivelArbol(Arbol *pa, int nivel)
{
    if(!*pa)
        return 0;

    if(nivel == 0)
    {
        free((*pa)->dato);
        free(*pa);
        *pa = NULL;
        return 1;
    }

    return eliminarNivelArbol(&(*pa)->izq, nivel - 1) && eliminarNivelArbol(&(*pa)->der, nivel - 1);
}

int podarArbol(Arbol *pa, int nivel)
{
    if(!*pa)
        return 0;

    if(nivel == 0)
        return vaciarArbol(pa);

    return podarArbol(&(*pa)->izq, nivel - 1) && podarArbol(&(*pa)->der, nivel - 1);
}


int arbolCompletoHastaNivel(const Arbol *pa, int nivel)
{
    if(nivel == 0 || !*pa)
        return *pa? 1 : 0;

    return arbolCompletoHastaNivel(&(*pa)->izq, nivel - 1) && arbolCompletoHastaNivel(&(*pa)->der, nivel - 1);
}


int arbolCompleto(const Arbol *pa)
{
    if(!*pa)
        return 1;

    int hi = alturaArbol(&(*pa)->izq);
    int hd = alturaArbol(&(*pa)->der);

    if(hi != hd)
        return 0;

    return arbolCompleto(&(*pa)->izq) && arbolCompleto(&(*pa)->der);
}


int arbolAVL(const Arbol *pa)
{
    if(!*pa)
        return 1;

    int hi = alturaArbol(&(*pa)->izq);
    int hd = alturaArbol(&(*pa)->der);

    if(abs(hi - hd) > 1)
        return 0;

    return arbolAVL(&(*pa)->izq) && arbolAVL(&(*pa)->der);
}


int vaciarArbol(Arbol *pa)
{
    if(!*pa)
        return 0;

    int cni = vaciarArbol(&(*pa)->izq);
    int cnd = vaciarArbol(&(*pa)->der);

    free((*pa)->dato);
    free(*pa);

    *pa = NULL;
    return cni + cnd + 1;
}


int cargarArbol(Arbol *pa, size_t tam, const char *nomArch)
{
    FILE *arch;
    int cantReg;

    arch = fopen(nomArch, "rb");
    if(!arch)
        return 0;

    fseek(arch, 0, SEEK_END);
    cantReg = ftell(arch) / tam;

    cargarArbolRec(arch, pa, tam, 0, cantReg - 1);

    fclose(arch);
    return 1;
}


int cargarArbolRec(FILE *arch, Arbol *pa, size_t tam, int ini, int fin)
{
    Nodo *nue;
    int med;

    if(ini > fin)
        return 1;

    nue = (Nodo *)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }
    nue->tam = tam;
    nue->izq = nue->der = NULL;

    med = (ini + fin) / 2;

    fseek(arch, med * tam, SEEK_SET);
    fread((*pa)->dato, tam, 1, arch);

    *pa = nue;

    return cargarArbolRec(arch, &(*pa)->izq, tam, ini, med - 1) && cargarArbolRec(arch, &(*pa)->der, tam, med + 1, fin);
}


int grabarArbol(const Arbol *pa, const char *nomArch)
{
    FILE *arch;

    arch = fopen(nomArch, "wb");
    if(!arch)
        return 0;

    recorrerArbolEnOrden(*pa, accionGrabarRegistro, arch);

    fclose(arch);
    return 1;
}


void accionGrabarRegistro(void *dato, void *datosAccion)
{
    Nodo *nodo = (Nodo *)dato;
    FILE *arch = (FILE *)datosAccion;

    fwrite(nodo->dato, nodo->tam, 1, arch);
}


int eliminarDeArbol(Arbol *pa, void *dato, size_t tam, Cmp cmp)
{
    Arbol *pnae = buscarNodo(pa, dato, cmp);

    if(!pnae)
        return 0;

    memcpy(dato, (*pnae)->dato, MIN(tam, (*pnae)->tam));
    eliminarNodo(pnae);

    return 1;
}

int esHoja(const Arbol *pa)
{
    return !(*pa)->izq && !(*pa)->der;
}


void eliminarNodo(Arbol *pnae)
{
    Arbol *pnReemp;

    if(esHoja(*pnae))
    {
        free((*pnae)->dato);
        free(*pnae);
        return;
    }

    int hi = alturaArbol(&(*pnae)->izq);
    int hd = alturaArbol(&(*pnae)->der);


    pnReemp = hi > hd ? nodoMayor(&(*pnae)->izq) : nodoMenor(&(*pnae)->der);

    free((*pnae)->dato);
    (*pnae)->dato = (*pnReemp)->dato;

    Nodo *hijoReemp = (*pnReemp)->izq? (*pnReemp)->izq : (*pnReemp)->der;
    free(*pnReemp);

    *pnReemp = hijoReemp;
}


Arbol *nodoMenor(const Arbol *pa)
{
    if(!(*pa)->izq)
        return pa;

    return nodoMenor(&(*pa)->izq);
}


Arbol *nodoMayor(const Arbol *pa)
{
    if(!(*pa)->der)
        return pa;

    return nodoMayor(&(*pa)->der);
}


Arbol *buscarNodo(const Arbol *pa, const void *dato, Cmp cmp)
{
    if(!pa)
        return NULL;

    int comp = cmp(dato, (*pa)->dato);
    if(comp == 0)
        return (Arbol *)pa;

    return comp < 0? buscarNodo(&(*pa)->izq, dato, cmp) : buscarNodo(&(*pa)->der, dato, cmp);
}



int insertarEnArbol(Arbol *pa, const void *dato, size_t tam, Cmp cmp, Actualizar actualizar)
{
    int comp;
    Nodo *nue;

    while (*pa && (comp = cmp(dato, (*pa)->dato) != 0))
        pa = comp < 0? &(*pa)->izq : &(*pa)->der;

    if(*pa)
    {
        actualizar((*pa)->dato, dato);
        return 2; /// Dato repetido
    }

    nue = (Nodo *)malloc(sizeof(Nodo));
    if(!nue)
        return 0; /// Sin memoria

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0; /// Sin memoria
    }

    nue->tam = tam;
    memcpy(nue->dato, dato, tam);

    nue->izq = nue->der = NULL;
    *pa = nue;

    return 1;
}


int buscarEnArbol(const Arbol *pa, void *dato, size_t tam, Cmp cmp)
{
    int comp;

    while (*pa && (comp = cmp(dato, (*pa)->dato) != 0))
        pa = comp < 0? &(*pa)->izq : &(*pa)->der;

    if(!*pa)
        return 0;

    memcpy(dato, (*pa)->dato, MIN(tam, (*pa)->tam));

    return 1;
}


int alturaArbol(const Arbol *pa)
{
    if(!*pa)
        return 0;

    return MAX(alturaArbol(&(*pa)->izq), alturaArbol(&(*pa)->der)) + 1;
}


int cantElementosArbol(const Arbol *pa)
{
    if(!*pa)
        return 0;

    return 1 + cantElementosArbol(&(*pa)->izq) + cantElementosArbol(&(*pa)->der);
}


void recorrerArbolEnPreOrden(const Arbol *pa, Accion accion, void *param)
{
    if(!*pa)
        return;

    accion((*pa)->dato, param);
    recorrerArbolEnPreOrden(&(*pa)->izq, accion, param);
    recorrerArbolEnPreOrden(&(*pa)->der, accion, param);
}


void recorrerArbolEnOrden(const Arbol *pa, Accion accion, void *param)
{
    if(!*pa)
        return;

    recorrerArbolEnOrden(&(*pa)->izq, accion, param);
    accion((*pa)->dato, param);
    recorrerArbolEnOrden(&(*pa)->der, accion, param);
}

void recorrerArbolEnPosOrden(const Arbol *pa, Accion accion, void *param)
{
    if(!*pa)
        return;

    recorrerArbolEnPosOrden(&(*pa)->izq, accion, param);
    recorrerArbolEnPosOrden(&(*pa)->der, accion, param);
    accion((*pa)->dato, param);
}


void crearArbol(Arbol *pa)
{
    *pa = NULL;
}
///Arbol
typedef struct sNodo
{
    void *info;
    unsigned tamBytes;
    struct sNodo *izq;
    struct sNodo *der;
}tNodo;


typedef tNodo *Arbol;


void cargarArbolIn(Arbol *pa, const char *nombreArch) ///carga desde archivo al arbol
{
    FILE *pArb = fopen(nombreArch, "rb");

    int ls, li, cantRegistros;

    if(!pa)
        return;

    fseek(pArb, 0, SEEK_END); ///PARARSE AL FINAL DEL ARCHIVO
    cantRegistros = ftell(pArb) / sizeof(Idx); ///OBTENER CANTIDAD DE REGISTROS

    li = 0;
    ls = cantRegistros - 1;

    cargarArbolInOrden(pa, pArb, li, ls);

    fclose(pArb);
}


void cargarArbolInOrden(Arbol *pa, FILE *pArb, int li, int ls)
{
    Idx indice;
    int pm;

    if(ls < li)
        return;

    pm = (ls + li) / 2;

    fseek(pArb, pm * sizeof(Idx), SEEK_SET);
    fread(&indice, sizeof(Idx), 1, pArb);

    insertarEnArbol(pa, &indice, sizeof(Idx), compararIdx);
    cargarArbolInOrden(pa, pArb, pm + 1, ls);
    cargarArbolInOrden(pa, pArb, li, pm - 1);

}


void mostrarArchivoBin(const char *nombre,  void *dato, unsigned tamBytes, void mostrar(const void * d1))
{
    FILE *p = fopen(nombre, "rb");
    if(!p)
        return;

    rewind(p);

    fread(dato, tamBytes, 1, p);

    while(!feof(p))
    {
        mostrar(dato);
        fread(dato, tamBytes, 1, p);
    }

    fclose(p);
}


int buscarEmpleadoPorDni(Arbol *pArb, const void *dato, unsigned tamBytes, void *dato2, int cmp(const void *d1, const void *d2))
{
    FILE *pArch = fopen("Empleados.dat", "rb");
    Arbol *pa;
    Idx empIdx;
    void *d1 = malloc(tamBytes);

    if(!d1)
        return 0;

    memcpy(d1, dato, tamBytes);

    if((pa = buscarNodoAElim(pArb, d1, cmp)) != NULL)
    {
        memcpy(&empIdx, (*pa)->info, minimo(sizeof(Idx), (*pa)->tamBytes));
        fseek(pArch, empIdx.pos * sizeof(Empleado) , SEEK_SET);
        fread(dato2, sizeof(Empleado), 1, pArch);

        fclose(pArch);
        free(d1);
        return 1;
    }
    else
    {
        fclose(pArch);
        free(d1);
        return 0;
    }

}


void cargarArbol(Arbol *pa)
{
    FILE *pArch = fopen("Empleados.dat", "rb");
    Empleado emp;
    Idx empIdx;
    int pos = 0;

    if(!pArch)
        return;

    fread(&emp, sizeof(Empleado), 1, pArch);

    empIdx.dni = emp.dni;
    empIdx.pos = pos;

    while (!feof(pArch))
    {
        insertarEnArbol(pa, &empIdx, sizeof(empIdx), compararIdx);
        fread(&emp, sizeof(Empleado), 1, pArch);

        pos++;
        empIdx.dni = emp.dni;
        empIdx.pos = pos;
    }

    fclose(pArch);
}


void grabar(void *d1, FILE *pArch)
{
    Idx *indice = (Idx*)d1;

    fwrite(indice, sizeof(Idx), 1, pArch);
}

void trozarPedidos(char *linea, Pedidos *ped)
{
    char *aux = strchr(linea, '\n');
    *aux = '\0';

    aux = strrchr(linea, ';');
    sscanf(aux + 1, "%d", &ped->cantPedida);
    *aux = '\0';

    aux = strrchr(linea, ';');
    strcpy(ped->codProd, aux + 1);
    *aux = '\0';

    aux = strrchr(linea, ';');
    sscanf(aux + 1, "%d", &ped->codCliente);
    *aux = '\0';

    sscanf(linea, "%d/%d/%d", &ped->fecha.dia, &ped->fecha.mes, &ped->fecha.anio);
}


int actualizarEnArbol(Arbol *pArbol, void *dato, unsigned tamBytes,
                      int(*cmp)(const void *dato1, const void *dato2),
                      void(*acum)(void* dato, void* dato2, void *p), Cola *pc)
{
    int comp; ///variable de compacion

    while(*pArbol)///Mientras HayArbol
    {

        if((comp = cmp(dato, (*pArbol)->info)) < 0)
            pArbol = &(*pArbol)->izq;
        else if(comp > 0)
            pArbol = &(*pArbol)->der;
        else
        {
            acum(dato, (*pArbol)->info, pc);
            return 1;
        }
    }

    return 0;
}


int eliminarElemArbol(Arbol *pa, void *dato, unsigned tambytes, int comp(const void *d1, const void *d2))
{
    if(!(pa = buscarNodoAElim(pa, dato, comp)))
        return 0;
    memcpy(dato, (*pa)->info, minimo(tambytes, (*pa)->tamBytes));

    return eliminarNodoRaiz(pa);
}


tNodo **buscarNodoAElim(const Arbol *pa, const void *dato, int comp(const void *d1, const void *d2))
{
    int rComp;

    while (*pa && (rComp = comp(dato, (*pa)->info)))
    {
        if(rComp < 0)
            pa = &(*pa)->izq;
        else
            pa = &(*pa)->der;
    }

    if(!*pa)
        return NULL;


    return (tNodo **)pa;
}


int eliminarNodoRaiz(Arbol *pa)
{
    tNodo **remp, *elim;

    if(!*pa)
        return 0;

    free((*pa)->info);

    if(!(*pa)->izq && !(*pa)->der)
    {
        free(*pa);
        *pa = NULL;
        return 1;
    }

    remp = alturaArbol(&(*pa)->izq) > alturaArbol(&(*pa)->der) ? mayorNodoArbol(&(*pa)->izq) : menorNodoArbol(&(*pa)->der);

    elim = *remp;
    (*pa)->info = elim->info;
    (*pa)->tamBytes = elim->tamBytes;

    *remp = elim->izq ? elim->izq : elim->der;

    free(elim);

    return 1;
}


tNodo ** menorNodoArbol(const Arbol *pa)
{
    if(!*pa)
        return NULL;
    while ((*pa)->izq)
        pa = &(*pa)->izq;

    return (tNodo **)pa;
}


tNodo ** mayorNodoArbol(const Arbol *pa)
{
    if(!*pa)
        return NULL;
    while ((*pa)->der)
        pa = &(*pa)->der;

    return (tNodo **)pa;
}



int esArbolAvl(const Arbol *pa)
{
    int hd = alturaArbol(&(*pa)->der);
    int hi = alturaArbol(&(*pa)->izq);

    if(!*pa)
        return 1;


    if ((hi - hd) > 1)
        return 0;

    return esArbolAvl(&(*pa)->der) && esArbolAvl(&(*pa)->izq);
}


unsigned alturaArbol(const Arbol *pa)
{
    int hi, hd;

    if(!*pa)
        return 0;
    hi = alturaArbol(&(*pa)->izq);
    hd = alturaArbol(&(*pa)->der);

    return (hi > hd? hi : hd) + 1;
}


void vaciarArbol(Arbol *pa)
{
    if(!*pa)
        return;
    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);

    free((*pa)->info);
    free((*pa));

    *pa = NULL;
}


int contarNodos(Arbol *pa)
{
    if(!*pa)
        return 0;
    return contarNodos(&(*pa)->izq) + contarNodos(&(*pa)->der) + 1;
}


void mostrarArbolPosOrden(Arbol *pa, void accion(const void *d1))
{
    if(!*pa)
        return;

    mostrarArbolPosOrden(&(*pa)->izq, accion);
    mostrarArbolPosOrden(&(*pa)->der, accion);
    accion((*pa)->info);
}


void mostrarArbolPreOrden(Arbol *pa, void accion(void *d1))
{
    if(!*pa)
        return;
    accion((*pa)->info);
    mostrarArbolPreOrden(&(*pa)->izq, accion);
    mostrarArbolPreOrden(&(*pa)->der, accion);
}


void guardarIndiceArbol(Arbol *pa, FILE *pARch, void accion(void *d1, FILE *pArch))
{
    if(!*pa)
        return;

    accion((*pa)->info, pARch);
    guardarIndiceArbol(&(*pa)->izq, pARch, accion);
    guardarIndiceArbol(&(*pa)->der, pARch, accion);
}


void guardarIndiceArbolPreOrden(Arbol *pa, void accion(void *d1, FILE *pArch)) 
{
    FILE *pArch = fopen(ARCH_BIN_IDX, "wb");
    if(!pArch)
        return;
    if(!*pa)
        return;
    guardarIndiceArbol(pa, pArch, accion);
    fclose(pArch);
}


void guardarIndiceArbolIn(Arbol *pa, FILE *pARch, void accion(void *d1, FILE *pArch))
{
    if(!*pa)
        return;

    guardarIndiceArbolIn(&(*pa)->izq, pARch, accion);
    accion((*pa)->info, pARch);
    guardarIndiceArbolIn(&(*pa)->der, pARch, accion);
}


void guardarIndiceArbolInOrden(Arbol *pa, void accion(void *d1, FILE *pArch))
{
    FILE *pArch = fopen("tempIdx.dat", "wb");
    if(!pArch)
        return;
    if(!*pa)
        return;
    guardarIndiceArbolIn(pa, pArch, accion);
    fclose(pArch);
}


void mostrarArbolInOrden(Arbol *pa, int n, void accion(const void *d1))
{
    int i;
    if(!*pa)
        return;

    mostrarArbolInOrden(&(*pa)->izq, n + 1, accion);
    for(i = 0; i < n; i++)
        printf("    ");

    accion((*pa)->info);
    mostrarArbolInOrden(&(*pa)->der, n + 1, accion);
}


int insertarEnArbol(Arbol *pa, const void *dato, unsigned tamBytes, int (cmp)(const void *d1, const void *d2))
{
    tNodo *nue;
    int comp;

    if(*pa)
    {
        if((comp = cmp(dato, (*pa)->info)) < 0)
            return insertarEnArbol(&(*pa)->izq, dato, tamBytes, cmp);
        if(comp > 0)
            return insertarEnArbol(&(*pa)->der, dato, tamBytes, cmp);
        if(comp == 0)
            return 0;
    }

    nue = malloc(sizeof(tNodo));

    if(!nue)
        return 0;
    nue->info = malloc(tamBytes);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, tamBytes);
    nue->tamBytes = tamBytes;

    nue->izq = NULL;
    nue->der = NULL;

    *pa = nue;

    return 1;
}


void crearArbol(Arbol *pa)
{
    *pa = NULL;
}

///Fin Arbol


///Lista Doble 
typedef struct sNodo
{
    void *dato;
    size_t tam;
    struct sNodo *sig, *ant;
}Nodo;

typedef Nodo *Lista;
typedef int (*Cmp)(const void *, const void *);


int listaLlena(const Lista *pl, size_t tam)
{
    void *nue = malloc(sizeof(Nodo));
    void *dato = malloc(tam);

    free(nue);
    free(dato);

    return !nue || !dato;
}

int listaVacia(const Lista *pl)
{
    return *pl == NULL;
}


void vaciarLista(Lista *pl)
{
    Nodo *act = *pl;

    while (act->ant)
        act = act->ant;
    while (act)
    {
        Nodo *aux = act->sig;
        free(act->dato);
        free(act);
        act = aux;
    }
    *pl = NULL;

}


int anteriorLista(Lista *pl, void *dato, size_t tam)
{
    if(!*pl || !(*pl)->ant)
        return 0;

    *pl = (*pl)->ant;

    memcpy(dato, (*pl)->dato, MEN(tam, (*pl)->tam));

    return 1;
}


int siguienteLista(Lista *pl, void *dato, size_t tam)
{
    if(!*pl || !(*pl)->sig)
        return 0;

    *pl = (*pl)->sig;

    memcpy(dato, (*pl)->dato, MEN(tam, (*pl)->tam));

    return 1;
}


int ultimoLista(Lista *pl, void *dato, size_t tam)
{
    if(!*pl)
        return 0;

    while((*pl)->sig)
        *pl = (*pl)->sig;

    memcpy(dato, (*pl)->dato, MEN(tam, (*pl)->tam));

    return 1;
}


int primeroLista(Lista *pl, void *dato, size_t tam)
{
    if(!*pl)
        return 0;

    while((*pl)->ant)
        *pl = (*pl)->ant;

    memcpy(dato, (*pl)->dato, MEN(tam, (*pl)->tam));

    return 1;
}

int sacarElemLista(Lista *pl, void *dato, size_t tam, Cmp cmp)
{
    Nodo *elim = *pl;

    if(!elim)
        return 0;

    while (elim && cmp(dato, elim->dato) < 0)
        elim = elim->ant;

    while (elim && cmp(dato, elim->dato) > 0)
        elim = elim->sig;

    if(!elim || cmp(dato, elim->dato) != 0)
        return 2; ///No se encontro el dato

    if(elim->ant)
        elim->ant->sig = elim->sig;

    if(elim->sig)
        elim->sig->ant = elim->ant;

    *pl = elim->sig? elim->sig : elim->ant;

    free(elim->dato);
    free(elim);

    return 1;
}


void mostrarListaDeIzqADer(Lista *pl, Mostrar mostrar)
{
    Nodo *act = *pl;

    while (act->sig)
        act = act->sig;

    while (act)
    {
        mostrar(act->dato);
        act = act->ant;
    }
}


void mostrarListaDeDerAIzq(Lista *pl, Mostrar mostrar)
{
    Nodo *act = *pl;

    while (act->ant)
        act = act->ant;

    while (act)
    {
        mostrar(act->dato);
        act = act->sig;
    }
}

int insertarOrdenado(Lista *pl, void *dato, size_t tam, Cmp cmp)
{
    Nodo *nue, *auxSig, *auxAnt;

    auxSig = *pl;
    auxAnt = auxSig? auxSig->ant : NULL;

    while (auxAnt && cmp(dato, auxAnt->dato) < 0)
    {
        auxSig = auxAnt;
        auxAnt = auxSig->ant;
    }

    while (auxSig && cmp(dato, auxSig->dato) > 0)
    {
        auxAnt = auxSig;
        auxSig = auxSig->sig;
    }

    if((auxAnt && cmp(dato, auxAnt->dato) == 0) || (auxSig && cmp(dato, auxSig->dato) == 0))
        return 11; //duplicado

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;

    nue->sig = auxSig;
    nue->ant = auxAnt;

    if(auxAnt)
        auxAnt->sig = nue;
    if(auxSig)
        auxSig->ant = nue;

    *pl = nue;

    return 1;
}


int insertarAlFinalLista(Lista *pl, const void *dato, size_t tam)
{
    Nodo *act = *pl, *nue;

    while(act)
        act = act->sig;

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;

    nue->sig = NULL;
    nue->ant = act;

    if(act)
        act->sig = nue;

    *pl = nue;
    return 1;
}


int insertarAlPrincipioLista(Lista *pl, const void *dato, size_t tam)
{
    Nodo *act= *pl, *nue;

    while(act->ant)
        act = act->ant;

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;

    nue->sig = act;
    nue->ant = NULL;

    if(act)
        act->ant = nue;

    *pl = nue;
    return 1;
}


void crearLista(Lista *pl)
{
    *pl = NULL;
}
///Fin Lista Doble

///Lista Simple 

typedef struct sNodo
{
    void *dato;
    size_t tamElem;
    struct sNodo *sig;
}Nodo;


typedef Nodo *Lista;

void recorrerLista(const Lista *pl, void *extra, Accion accion)
{
    while (*pl)
    {
        accion((*pl)->dato, extra);
        pl = &(*pl)->sig;
    }
}


void ordenarLista(Lista *pl, Cmp cmp)
{
    Lista lOrd = NULL; /// Lista ordenada
    Lista *plOrd; /// Puntero a la lista ordenada
    Nodo *nodo; /// Nodo a insertar

    while (*pl)
    {
        nodo = *pl;
        *pl = nodo->sig;
        plOrd = &lOrd;

        while (*plOrd && cmp(nodo->dato, (*plOrd)->dato) > 0)
            plOrd = &(*plOrd)->sig;

        nodo->sig = *plOrd;
        *plOrd = nodo;
    }
    *pl = lOrd;
}


int sacarElementoParticular(Lista* pl, void* pd, size_t tam, void *elemSacar, Cmp cmp)
{
    Nodo *nae;

    if(!*pl)
        return 0;

    while (*pl && cmp(elemSacar, (*pl)->dato) != 0)
        pl = &(*pl)->sig;

    nae = *pl;

    memcpy(pd, nae->dato, MIN(nae->tamElem, tam));

    *pl = nae->sig;

    free(nae->dato);
    free(nae);

    return 1;
}


int sacarFinal(Lista *pl, void *pd, size_t tam)
{
    Nodo *nae;

    if(!*pl)
        return 0;

    while (*pl)
        pl = &(*pl)->sig;

    nae = *pl;

    memcpy(pd, nae->dato, MIN(nae->tamElem, tam));

    *pl = NULL;

    free(nae->dato);
    free(nae);

    return 1;
}


int verUltimoLista(const Lista *pl, void *pd, size_t tam)
{
    if(!*pl)
        return 0;

    while((*pl)->sig)
        pl = &(*pl)->sig;
    memcpy(pd, (*pl)->dato, MIN(tam, (*pl)->tamElem));
    return 1;
}


int sacarInicioLista(Lista *pl, void *pd, size_t tam)
{
    Nodo *nae;

    if(!*pl)
        return 0;

    nae = *pl;

    memcpy(pd, nae->dato, MIN(nae->tamElem, tam));

    *pl = nae->sig;

    free(nae->dato);
    free(nae);

    return 1;
}


int verPrimeroLista(const Lista *pl, void *pd, size_t tam)
{
    if(!*pl)
        return 0;
    memcpy(pd, (*pl)->dato, MIN(tam, (*pl)->tamElem));
    return 1;

}


int ponerEnOrdenLista(Lista *pl, const void *pd, size_t tam, Cmp cmp)
{
    Nodo *nue;
    int comp;

    while (*pl && (comp = cmp(pd, (*pl)->dato) > 0))
        pl = &(*pl)->sig;

    if(!*pl && !comp)
        return -12;

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}


int ponerEnPosicionLista(Lista* pl, const void* pd, size_t tam, unsigned pos)
{
    Nodo *nue;

    while (*pl && pos)
    {
        pl = &(*pl)->sig;
        pos--;
    }

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}


int ponerAlComienzoLista(Lista *pl, const void *pd, size_t tam)
{
    Nodo *nue;

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;
    return 1;

}


int ponerAlFinalLista(Lista *pl, const void *pd, size_t tam)
{
    Nodo *nue;

    while(*pl)
        pl = &(*pl)->sig;

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}


void vaciarLista(Lista *pl)
{
    while(*pl)
    {
        Nodo *aux = *pl;

        *pl = aux->sig;
        free(aux->dato);
        free(aux);
    }
    *pl = NULL;
}


void crearLista(Lista *pl)
{
    *pl = NULL;
}
///Fin Lista Simple


///Cola Dinamica 
typedef struct sNodo
{
    void *dato;
    size_t tam;
    struct sNodo *sig;
}Nodo;


typedef struct
{
    Nodo *pri;
    Nodo *ult;
}Cola;

int colaLlena(const Cola *pc, size_t tam)
{
    void *nodo = malloc(sizeof(Nodo));
    void *dato = malloc(tam);

    free(nodo);
    free(dato);

    return !nodo || !dato;
}


int colaVacia(const Cola *pc)
{
    return !pc->pri;
}


void vaciarCola(Cola *pc)
{
    Nodo *elim;

    while (pc->pri)
    {
        elim = pc->pri;
        pc->pri = elim->sig;
        free(elim->dato);
        free(elim);
    }

    pc->ult = NULL;
}


int verFrenteCola(const Cola *pc, void *dato, size_t tam)
{
    if(!pc->pri)
        return 0;
    memcpy(dato, pc->pri->dato, MINIMO(tam, pc->pri->tam));
    return 1;
}


int sacarDeCola(Cola *pc, void *dato, size_t tam)
{
    Nodo *elim;
    elim = pc->pri;

    if(!elim)
        return 0;

    memcpy(dato, elim->dato, MINIMO(tam, elim->tam));

    pc->pri = elim->sig;

    if(!pc->pri)
        pc->ult = NULL;

    free(elim->dato);
    free(elim);

    return 1;
}


int ponerEnCola(Cola *pc, const void *dato, size_t tam)
{
    Nodo *nue;
    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;
    nue->sig = NULL;

    if(pc->ult)
        pc->ult->sig = nue;
    else
        pc->pri = nue;

    pc->ult = nue;

    return 1;
}


void crearCola(Cola *pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}
///Fin Cola

/// Pila Dinamica
typedef struct sNodo
{
    void* dato;
    size_t tamBytes;
    struct sNodo *sig;
}Nodo;

typedef Nodo *Pila;
void crearPila(Pila *pp)
{
    *pp = NULL;
}


int ponerEnPila(Pila *pp, const void *dato, size_t cantBytes)
{
    Nodo *nue;
    nue = (Nodo*)malloc(sizeof(Nodo));

    if(!nue)
        return 0;

    nue->dato = malloc(cantBytes);

    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    nue->tamBytes = cantBytes;
    memcpy(nue->dato, dato, cantBytes);

    nue->sig = *pp;
    *pp = nue;

    return 1;
}


int sacarDePila(Pila *pp, void *dato, size_t cantBytes)
{
    Nodo *elim;

    if(!*pp)
        return 0;

    elim = *pp;
    *pp = elim->sig;

    memcpy(dato, elim->dato, MINIMO(elim->tamBytes, cantBytes));

    free(elim->dato);
    free(elim);

    return 1;
}


int pilaVacia(const Pila *pp)
{
    return *pp == NULL;
}


int pilaLlena(const Pila *pp, size_t cantBytes)
{
    void *nodo = malloc(sizeof(Nodo));
    void *dato = malloc(cantBytes);

    free(nodo);
    free(dato);

    return nodo == NULL || dato == NULL;
}


int verTope(const Pila *pp, void *dato, size_t cantBytes)
{
    Nodo *tope;

    tope = *pp;

    if(!tope)
        return 0;

    memcpy(dato, tope->dato, MINIMO(cantBytes, tope->tamBytes));

    return 1;

}


void vaciarPila(Pila *pp)
{
    Nodo *elim;

    while(*pp)
    {
        elim = *pp;
        *pp = elim->sig;

        free(elim->dato);
        free(elim);
    }
}
/// Fin pila
