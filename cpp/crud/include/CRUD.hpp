#pragma once

#include "Sistema.hpp"

class CRUD{

    Sistema sistema;

    public:
        CRUD();
        void menu();
        void relatorio();
        void create();
        void read();
        void upd();
        void del();
};