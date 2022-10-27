/*
 * Thu Oct 27 18:58:15 2022
 * This file was produced by
 *   rtt: Unicon Version 13.3 (iconc).  October 27, 2022
 */
#define COMPILER 0
#include "/root/unicon/bin/../src/h/rt.h"


#line 22 "fsys.r"

extern int errno;
int Zclose (dptr r_args);
FncBlock(close, 1, 0)

int Zclose(r_args)
dptr r_args;
   {

#line 34 "fsys.r"

   if (!((r_args[1]).dword == D_File)) {
      {
      err_msg(

#line 35 "fsys.r"

      105, &(r_args[1]));
      return A_Resume;
      }
      }

#line 41 "fsys.r"

   {

#line 45 "fsys.r"

   FILE *fp = BlkD(r_args[1], File)->fd.fp; 
   int status = BlkD(r_args[1], File)->status;
   CURTSTATE();

   if ((status & (Fs_Read | Fs_Write)) == 0) 
      {
      r_args[0] = 

#line 49 "fsys.r"

         r_args[1];
      return A_Continue;
      }

#line 55 "fsys.r"

   if (status & Fs_Messaging) {
      BlkLoc(r_args[1])->File.status = 0;
      {
      r_args[0].vword.integr = 

#line 57 "fsys.r"

         Mclose(BlkD(r_args[1], File)->fd.mf);
      r_args[0].dword = D_Integer;
      return A_Continue;
      }
      }
   if (BlkD(r_args[1], File)->status & Fs_Socket) {
      BlkLoc(r_args[1])->File.status = 0;
      StrLoc(BlkLoc(r_args[1])->File.fname) = "closed socket";
      StrLen(BlkLoc(r_args[1])->File.fname) = 13;
      {
      r_args[0].vword.integr = 

         close(BlkLoc(r_args[1])->File.fd.fd);
      r_args[0].dword = D_Integer;
      return A_Continue;
      }
      }

#line 76 "fsys.r"

   if (BlkD(r_args[1], File)->status & Fs_Directory) {
      BlkLoc(r_args[1])->File.status = 0;
      closedir((DIR *)fp);
      {
      r_args[0] = 

#line 79 "fsys.r"

         r_args[1];
      return A_Continue;
      }
      }

#line 107 "fsys.r"

   if (BlkD(r_args[1], File)->status & Fs_Pty) {
      ptclose(BlkLoc(r_args[1])->File.fd.pt);
      {
      r_args[0].vword.integr = 

#line 109 "fsys.r"

         0;
      r_args[0].dword = D_Integer;
      return A_Continue;
      }
      }
   if (BlkD(r_args[1], File)->status & Fs_Dbm) {
      BlkLoc(r_args[1])->File.status = 0;
      dbm_close((DBM *)fp);
      {
      r_args[0] = 

#line 117 "fsys.r"

         r_args[1];
      return A_Continue;
      }
      }

#line 167 "fsys.r"

   if ((BlkD(r_args[1], File)->status & Fs_Pipe)) {
      int rv;
      BlkLoc(r_args[1])->File.status = 0;
      if ((rv = pclose(fp)) == -1) {
         IntVal(amperErrno) = errno;
         return A_Resume;
         }
      {
      r_args[0].vword.integr = 

#line 174 "fsys.r"

         ((rv >> 8) & 0377);
      r_args[0].dword = D_Integer;
      return A_Continue;
      }
      }
   else 

#line 178 "fsys.r"

   if (fclose(fp) != 0) {
      IntVal(amperErrno) = errno;
      return A_Resume;
      }

   BlkLoc(r_args[1])->File.status = 0;
   {
   r_args[0] = 

#line 188 "fsys.r"

      r_args[1];
   return A_Continue;
   }
   }
   }

#undef exit

int Zexit (dptr r_args);
FncBlock(exit, 1, 0)

int Zexit(r_args)
dptr r_args;
   {
   C_integer r_i0;

#line 198 "fsys.r"

   if (!def_c_int(&(r_args[1]), EXIT_SUCCESS, &(r_i0))) {
      {
      err_msg(

#line 199 "fsys.r"

      101, &(r_args[1]));
      return A_Resume;
      }
      }

#line 200 "fsys.r"

   {

#line 209 "fsys.r"

   if (r_i0 == 10101) {

#line 214 "fsys.r"

      CURTSTATE();

#line 217 "fsys.r"

      coclean(BlkD(k_current, Coexpr));
      }

#line 221 "fsys.r"

   c_exit((int)r_i0);
   return A_Resume;
   }
   }

int Zgetenv (dptr r_args);
FncBlock(getenv, 1, 0)

int Zgetenv(r_args)
dptr r_args;
   {

#line 236 "fsys.r"

   if (!cnv_c_str(&(r_args[1]), &(r_args[1]))) {
      {
      err_msg(

#line 237 "fsys.r"

      103, &(r_args[1]));
      return A_Resume;
      }
      }

   {
   char *p, *sbuf; 
   long l;

   if ((sbuf = getenv_var(r_args[1].vword.sptr)) != NULL) {
      l = strlen(sbuf);
      do {if ((p = alcstr(sbuf, l)) == NULL) {
            err_msg(0, NULL);
            return A_Resume;
            }
         }
      while (0);

#line 249 "fsys.r"

      free(sbuf);
      {
      r_args[0].vword.sptr = 

#line 250 "fsys.r"

         p;
      r_args[0].dword = 

#line 250 "fsys.r"

         l;
      return A_Continue;
      }
      }
   else 

#line 252 "fsys.r"

      {
      set_syserrortext(errno);
      return A_Resume;
      }
   }
   }

int Zopen (int r_nargs, dptr r_args);
FncBlock(open, -3, 0)

int Zopen(r_nargs, r_args)
int r_nargs;
dptr r_args;
   {
   char r_sbuf[1][MaxCvtLen];
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[6];
      } r_tend;

   r_tend.d[5] = emptystr;
   r_tend.d[4] = emptystr;
   r_tend.d[3] = emptystr;
   r_tend.d[2] = nullptr;
   r_tend.d[1] = emptystr;
   r_tend.d[0].dword = D_Null;
   r_tend.num = 6;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;

#line 277 "fsys.r"

   if (!cnv_str(&(r_args[1]), &(r_args[1]))) {
      {
      err_msg(

#line 278 "fsys.r"

      103, &(r_args[1]));
      tend = r_tend.previous;
      return A_Resume;
      }
      }
   if (!def_tstr(r_sbuf[0], &(r_args[2]), &(letr), &(r_args[2]))) {
      {
      err_msg(

#line 284 "fsys.r"

      103, &(r_args[2]));
      tend = r_tend.previous;
      return A_Resume;
      }
      }

   { 

   char home_sbuf[1024]; 
   register word slen; 
   register int i; 
   register char *s; 
   int status; 
   char mode[4]; 
   extern FILE *fopen(); 
   FILE *f = NULL; 
   SOCKET fd; 

#line 303 "fsys.r"

   struct stat st; 

#line 312 "fsys.r"

   int is_shortreq = 0; 
   int do_verify = 1; 

#line 330 "fsys.r"

   int is_udp_or_listener = 0; 

#line 333 "fsys.r"

   int is_ipv4 = 0; 
   int is_ipv6 = 0; 
   int af_fam; 

#line 339 "fsys.r"

   extern FILE *popen();

#line 349 "fsys.r"

   set_syserrortext(0);

#line 354 "fsys.r"

   if (!cnv_c_str(&(r_args[1]), &(r_tend.d[1]))) 
      {
      err_msg(

#line 355 "fsys.r"

      103, &(r_args[1]));
      tend = r_tend.previous;
      return A_Resume;
      }

#line 358 "fsys.r"

   if (strlen(r_tend.d[1].vword.sptr) != StrLen(r_args[1])) {
      set_errortext(218);
      {
      tend = r_tend.previous;
      return A_Resume;
      }
      }

#line 368 "fsys.r"

   if (r_tend.d[1].vword.sptr[0] == '~') {
      if (r_tend.d[1].vword.sptr[1] == '/') {
         getenv_r("HOME", home_sbuf, 1023);
         strcat(home_sbuf, r_tend.d[1].vword.sptr + 1);
         r_tend.d[1].vword.sptr = home_sbuf;
         }
      }

   status = 0;

#line 382 "fsys.r"

   s = StrLoc(r_args[2]);
   slen = StrLen(r_args[2]);

   for (i = 0; i < slen; i++) {
      switch (*s++) {
         case 'j': 
         case 'J': 
            status |= Fs_Encrypt;
            continue;
         case 'a': 
         case 'A': 
            status |= Fs_Write | Fs_Append;
            continue;
         case 'b': 
         case 'B': 
            status |= Fs_Read | Fs_Write;
            continue;
         case 'c': 
         case 'C': 
            status |= Fs_Create | Fs_Write;
            continue;
         case 'r': 
         case 'R': 
            status |= Fs_Read;
            continue;
         case 'w': 
         case 'W': 
            status |= Fs_Write;
            continue;
         case '-': 
            do_verify = 0;
            continue;
         case 's': 
         case 'S': 

            if (status & Fs_Messaging) {
               is_shortreq = 1;
               continue;
               }

            continue;

         case 't': 
         case 'T': 
            status &= ~Fs_Untrans;
            continue;

         case '6': 

            is_ipv6 = 1;
            continue;

         case '4': 

            is_ipv4 = 1;
            continue;

#line 440 "fsys.r"

         case 'u': 
         case 'U': 

            is_udp_or_listener = 1;

            if ((status & Fs_Socket) == 0) 
               status |= Fs_Untrans;
            continue;

#line 450 "fsys.r"

         case 'p': 
         case 'P': 
            status |= Fs_Pipe;
            continue;

#line 456 "fsys.r"

         case 'x': 
         case 'X': 
         case 'g': 
         case 'G': 

#line 477 "fsys.r"

            set_errortext(148);
            {
            tend = r_tend.previous;
            return A_Resume;
            }

#line 488 "fsys.r"

            set_errortext(1045);
            {
            tend = r_tend.previous;
            return A_Resume;
            }

#line 491 "fsys.r"

         case 'l': 
         case 'L': 

            if (status & Fs_Socket) {
               status |= Fs_Listen | Fs_Append;
               is_udp_or_listener = 2;
               continue;
               }

#line 506 "fsys.r"

            set_errortext(1045);
            {
            tend = r_tend.previous;
            return A_Resume;
            }
         case 'd': 
         case 'D': 

            status |= Fs_Dbm;
            continue;

#line 521 "fsys.r"

         case 'm': 
         case 'M': 

            status |= Fs_Messaging | Fs_Read | Fs_Write;
            continue;

#line 531 "fsys.r"

         case 'n': 
         case 'N': 

            status |= Fs_Socket | Fs_Read | Fs_Write | Fs_Unbuf;
            continue;

#line 543 "fsys.r"

         case 'o': 
         case 'O': 

#line 550 "fsys.r"

            set_errortext(1045);
            {
            tend = r_tend.previous;
            return A_Resume;
            }

#line 553 "fsys.r"

         case 'v': 
         case 'V': 

            if (status & Fs_Messaging) {
               status |= Fs_Verify;
               continue;
               }

#line 565 "fsys.r"

            set_errortext(1045);
            {
            tend = r_tend.previous;
            return A_Resume;
            }

#line 569 "fsys.r"

         case 'z': 
         case 'Z': 

#line 576 "fsys.r"

            set_errortext(1045);
            {
            tend = r_tend.previous;
            return A_Resume;
            }

#line 580 "fsys.r"

         default: 
            {
            err_msg(

#line 581 "fsys.r"

            209, &(r_args[2]));
            tend = r_tend.previous;
            return A_Resume;
            }
            }
      }

#line 595 "fsys.r"

   mode[0] = '\0';
   mode[1] = '\0';
   mode[2] = '\0';
   mode[3] = '\0';

#line 604 "fsys.r"

   SSL * ssl;

   if (status & Fs_Encrypt) 
      {

#line 611 "fsys.r"

      if (cnv_c_str(&((&r_args[3])[0]), &(r_tend.d[3]))) 

         if (cnv_c_str(&((&r_args[3])[1]), &(r_tend.d[4]))) 

#line 617 "fsys.r"

            SSL_library_init();
      SSL_CTX * ctx;

#line 622 "fsys.r"

      SSL_METHOD * method;

#line 625 "fsys.r"

      OpenSSL_add_all_algorithms();
      SSL_load_error_strings();

#line 629 "fsys.r"

      method = TLSv1_2_server_method();
      ctx = SSL_CTX_new(method);

#line 633 "fsys.r"

      if (ctx == NULL) 
         {
         ERR_print_errors_fp(stderr);
         abort();
         }

      SSL_CTX_set_cipher_list(ctx, "ALL:eNULL");

#line 647 "fsys.r"

      if (SSL_CTX_load_verify_locations(ctx, r_tend.d[3].vword.sptr, r_tend.d[4].vword.sptr) != 1) 
         ERR_print_errors_fp(stderr);
      else 

      if (SSL_CTX_set_default_verify_paths(ctx) != 1) 
         ERR_print_errors_fp(stderr);

#line 655 "fsys.r"

      if (SSL_CTX_use_certificate_file(ctx, r_tend.d[3].vword.sptr, SSL_FILETYPE_PEM) <= 0) 
         {
         ERR_print_errors_fp(stderr);
         abort();
         }

      SSL_CTX_set_default_passwd_cb_userdata(ctx, "12345678");
      if (SSL_CTX_use_PrivateKey_file(ctx, r_tend.d[4].vword.sptr, SSL_FILETYPE_PEM) <= 0) 
         {
         ERR_print_errors_fp(stderr);
         abort();
         }

      if (!SSL_CTX_check_private_key(ctx)) 
         {
         fprintf(stderr, "Private key does not match the public certificate\n");
         abort();
         }

#line 675 "fsys.r"

      ssl = SSL_new(ctx);
      }

#line 701 "fsys.r"

   if (!(status & Fs_Dbm)) 

#line 708 "fsys.r"

      if ((status & (Fs_Read | Fs_Write)) == 0) 
         status |= Fs_Read;
   if (status & Fs_Create) 
      mode[0] = 'w';
   else if (status & Fs_Append) 
      mode[0] = 'a';
   else if (status & Fs_Read) 
      mode[0] = 'r';
   else 
      mode[0] = 'w';

#line 731 "fsys.r"

   if ((status & (Fs_Read | Fs_Write)) == (Fs_Read | Fs_Write)) 
      mode[1] = '+';

#line 807 "fsys.r"

   if (status & Fs_Messaging) {
      C_integer timeout = 0, timeout_set = 0; 
      extern int Merror;
      if (do_verify != 0) 
         status |= Fs_Verify;
      if (status & ~(Fs_Messaging | Fs_Read | Fs_Write | Fs_Untrans | Fs_Verify)) {
         {
         err_msg(

#line 813 "fsys.r"

         209, &(r_args[2]));
         tend = r_tend.previous;
         return A_Resume;
         }
         }
      else 

#line 815 "fsys.r"

         {
         URI *puri; 
         register int a;

#line 820 "fsys.r"

         for (a = 0; a < (r_nargs - 2); a++) {
            if ((((&r_args[3])[a]).dword == D_Null)) {
               (&r_args[3])[a] = emptystr;
               }
            else if (a == 0 && cnv_c_int(&((&r_args[3])[a]), &(timeout))) {
               M_open_timeout = timeout;
               timeout_set = 1;
               }
            else if (!(!(((&r_args[3])[a]).dword & F_Nqual))) {
               {
               err_msg(

#line 829 "fsys.r"

               109, &((&r_args[3])[a]));
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }

#line 843 "fsys.r"

         if (is_ipv4 && is_ipv6) 
            af_fam = AF_UNSPEC;
         else if (is_ipv6) 
            af_fam = AF_INET6;
         else if (is_ipv4) 
            af_fam = AF_INET;
         else 
            af_fam = AF_UNSPEC;

#line 853 "fsys.r"

         puri = uri_parse(r_tend.d[1].vword.sptr, af_fam);
         switch (puri->status) {
            case URI_OK: 
               break;
            case URI_EMALFORMED: 
               {
               err_msg(

#line 858 "fsys.r"

               1201, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }

#line 859 "fsys.r"

               break;
            case URI_ENOUSER: 
               {
               err_msg(

#line 861 "fsys.r"

               1202, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }

#line 862 "fsys.r"

               break;
            case URI_EUNKNOWNSCHEME: 
               {
               err_msg(

#line 864 "fsys.r"

               1203, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }

#line 865 "fsys.r"

               break;
            case URI_ECHECKERRNO: 
            default: 

               if (errno != 0) {
                  set_syserrortext(errno);
                  }

               {
               err_msg(

#line 873 "fsys.r"

               1204, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 876 "fsys.r"

         f = (FILE *)Mopen(puri, &(&r_args[3])[timeout_set], (r_nargs - 2) - timeout_set, is_shortreq, status);
         if (Merror > 1200) {
            uri_free(puri);
            {
            err_msg(

#line 879 "fsys.r"

            Merror, &(r_args[1]));
            tend = r_tend.previous;
            return A_Resume;
            }
            }

#line 881 "fsys.r"

         uri_free(puri);
         switch (Merror) {
            case 0: 
               break;
            case TP_ECONNECT: 
               set_errortext(1205);
               {
               tend = r_tend.previous;
               return A_Resume;
               }

#line 888 "fsys.r"

            case TP_EHOST: 
               set_errortext(1206);
               {
               tend = r_tend.previous;
               return A_Resume;
               }

#line 891 "fsys.r"

            case TP_ESERVER: 
               {
               err_msg(

#line 892 "fsys.r"

               1212, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }

#line 893 "fsys.r"

               break;
            case TP_ETRUST: 
               set_errortext(1214);
               {
               tend = r_tend.previous;
               return A_Resume;
               }

#line 897 "fsys.r"

            case TP_EVERIFY: 
               set_errortext(1215);
               {
               tend = r_tend.previous;
               return A_Resume;
               }

#line 900 "fsys.r"

            case TP_EMEM: 
            case TP_EOPEN: 
            default: 
               {
               err_msg(

#line 903 "fsys.r"

               1200, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }

#line 904 "fsys.r"

               break;
               }
         }
      }
   else 

#line 954 "fsys.r"

   if (status == (Fs_Pipe | Fs_Read | Fs_Write)) {

      status = Fs_Pty | Fs_Read | Fs_Write;
      f = (FILE *)ptopen(r_tend.d[1].vword.sptr);
      }
   else 

#line 966 "fsys.r"

   if (status & Fs_Pipe) { 

      int c, fnamestrlen = strlen(r_tend.d[1].vword.sptr);r_tend.d[5].vword.sptr = 

#line 967 "fsys.r"

      NULL;

      if ((status != (Fs_Read | Fs_Pipe)) && (status != (Fs_Write | Fs_Pipe))) 
         {
         err_msg(

#line 970 "fsys.r"

         209, &(r_args[2]));
         tend = r_tend.previous;
         return A_Resume;
         }

#line 976 "fsys.r"

      do {if ((reserve(Strings, (fnamestrlen << 1) + PATH_MAX + 2)) == NULL) {
            err_msg(0, NULL);
            tend = r_tend.previous;
            return A_Resume;
            }
         }
      while (0);

#line 977 "fsys.r"

      r_tend.d[4].vword.sptr = alcstr(r_tend.d[1].vword.sptr, fnamestrlen + 1);
      r_tend.d[4].vword.sptr[fnamestrlen] = '\0';

      if ((r_tend.d[5].vword.sptr = strchr(r_tend.d[4].vword.sptr, ' ')) != NULL) *r_tend.d[5].vword.sptr = '\0';
      if (!strchr(r_tend.d[4].vword.sptr, '\\') && !strchr(r_tend.d[4].vword.sptr, '/')) {
         r_tend.d[3].vword.sptr = alcstr(NULL, PATH_MAX + fnamestrlen + 3);
         if (findonpath(r_tend.d[4].vword.sptr, r_tend.d[3].vword.sptr, PATH_MAX) == NULL) {
            set_errortext(1050);
            {
            tend = r_tend.previous;
            return A_Resume;
            }
            }

#line 987 "fsys.r"

         r_tend.d[1].vword.sptr = r_tend.d[3].vword.sptr;

#line 1001 "fsys.r"

         if (r_tend.d[5].vword.sptr) {
            strcat(r_tend.d[1].vword.sptr, " ");
            strcat(r_tend.d[1].vword.sptr, r_tend.d[5].vword.sptr + 1);
            }
         }

      f = popen(r_tend.d[1].vword.sptr, mode);
      if (NULL == f) {set_errortext(1052);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1009 "fsys.r"

      if (!strcmp(mode, "r")) {

         if ((c = getc(f)) == EOF) {
            if (0 == pclose(f)) {set_errortext(1053);
               }
            else 

#line 1012 "fsys.r"

               {set_errortext(1050);
               }
            {
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         else 

#line 1016 "fsys.r"

            ungetc(c, f);
         }
      }
   else 

#line 1023 "fsys.r"

   if (status & Fs_Dbm) {
      int mode;
      if ((status & Fs_Read && status & Fs_Write) || status == Fs_Dbm) {
         mode = O_RDWR | O_CREAT;
         status |= Fs_Read | Fs_Write;
         }
      else if (status & Fs_Write) {
         mode = O_WRONLY | O_CREAT;
         }
      else 
         mode = O_RDONLY;

      if ((f = (FILE *)dbm_open(r_tend.d[1].vword.sptr, mode, 0666)) == NULL) {
         set_errortext(191);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }
      }
   else 

#line 1053 "fsys.r"

      {
      int sd; 
      char buf[1024]; 
      int bytes;
      if (status & Fs_Socket) {
         if (is_ipv4 && is_ipv6) 
            af_fam = AF_UNSPEC;
         else if (is_ipv6) 
            af_fam = AF_INET6;
         else if (is_ipv4) 
            af_fam = AF_INET;
         else 
            af_fam = AF_UNSPEC;

#line 1068 "fsys.r"

         if (status & ~(Fs_Read | Fs_Write | Fs_Socket | Fs_Append | Fs_Unbuf | Fs_Listen | Fs_Encrypt)) 
            {
            err_msg(

#line 1069 "fsys.r"

            209, &(r_args[2]));
            tend = r_tend.previous;
            return A_Resume;
            }

#line 1070 "fsys.r"

         if (status & Fs_Append) {

            DEC_NARTHREADS;
            fd = sock_listen(r_tend.d[1].vword.sptr, is_udp_or_listener, af_fam);
            SSL_set_fd(ssl, fd);

#line 1078 "fsys.r"

            if (SSL_accept(ssl) == -1) {
               ERR_print_errors_fp(stderr);
               }
            else 

               {

#line 1087 "fsys.r"

               bytes = SSL_read(ssl, buf, sizeof((buf)));
               if (bytes > 0) 
                  {
                  buf[bytes] = 0;

                  SSL_write(ssl, "HTTP/1.1 200 OK", strlen(buf));
                  }
               else 
                  {
                  }
               }

            sd = SSL_get_fd(ssl);
            SSL_free(ssl);
            close(sd);
            printf("%d\n", fd);
            printf("%s\n", buf);
            INC_NARTHREADS_CONTROLLED;
            }
         else {
            C_integer timeout = 0;

            if ((r_nargs - 2) > 0 && !(((&r_args[3])[0]).dword == D_Null)) {
               if (!cnv_c_int(&((&r_args[3])[0]), &(timeout))) 
                  {
                  err_msg(

#line 1111 "fsys.r"

                  101, &((&r_args[3])[0]));
                  tend = r_tend.previous;
                  return A_Resume;
                  }
               }DEC_NARTHREADS;
            if (SSL_accept(ssl) == -1) {
               ERR_print_errors_fp(stderr);

#line 1122 "fsys.r"

               fd = sock_connect(r_tend.d[1].vword.sptr, is_udp_or_listener == 1, timeout, af_fam);
               }

#line 1139 "fsys.r"

            INC_NARTHREADS_CONTROLLED;
            }

#line 1145 "fsys.r"

         if (is_udp_or_listener == 2) 
            status = Fs_Socket | Fs_Listen;
         else if (is_udp_or_listener == 1) 
            status = Fs_Socket | Fs_Write;
         else 
            status = Fs_Socket | Fs_Read | Fs_Write;

         if (!fd) {
            set_syserrortext(errno);
            {
            tend = r_tend.previous;
            return A_Resume;
            }
            }

#line 1162 "fsys.r"

         StrLen(r_tend.d[0]) = strlen(r_tend.d[1].vword.sptr) + 1;
         StrLoc(r_tend.d[0]) = r_tend.d[1].vword.sptr;
         do {if (((*(struct b_file**)&r_tend.d[2].vword.bptr) = alcfile(0, status, &r_tend.d[0])) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1165 "fsys.r"

         (*(struct b_file**)&r_tend.d[2].vword.bptr)->fd.fd = fd;

         (*(struct b_file**)&r_tend.d[2].vword.bptr)->fd.ssl = ssl;
         {
         r_args[0].vword.bptr = (union block *)
            (*(struct b_file**)&r_tend.d[2].vword.bptr);
         r_args[0].dword = D_File;
         tend = r_tend.previous;
         return A_Continue;
         }
         }
      else 

#line 1172 "fsys.r"

      if (stat(r_tend.d[1].vword.sptr, &st) < 0) {

#line 1175 "fsys.r"

         if (strchr(r_tend.d[1].vword.sptr, '*') || strchr(r_tend.d[1].vword.sptr, '?')) {
            char tempbuf[1024];

#line 1183 "fsys.r"

            sprintf(tempbuf, "for i in %s; do if [ \"$i\" != \"%s\" ]; then echo \"$i\"; fi; done", r_tend.d[1].vword.sptr, r_tend.d[1].vword.sptr);
            status |= Fs_Pipe;
            f = popen(tempbuf, "r");

#line 1226 "fsys.r"

            if (f == NULL) {
               set_syserrortext(errno);
               {
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 1230 "fsys.r"

            StrLen(r_tend.d[0]) = strlen(r_tend.d[1].vword.sptr);
            StrLoc(r_tend.d[0]) = r_tend.d[1].vword.sptr;
            do {if (((*(struct b_file**)&r_tend.d[2].vword.bptr) = alcfile(f, status, &r_tend.d[0])) == NULL) {
                  err_msg(0, NULL);
                  tend = r_tend.previous;
                  return A_Resume;
                  }
               }
            while (0);
            {
            r_args[0].vword.bptr = (union block *)
               (*(struct b_file**)&r_tend.d[2].vword.bptr);
            r_args[0].dword = D_File;
            tend = r_tend.previous;
            return A_Continue;
            }
            }
         else 

#line 1244 "fsys.r"

         if (errno == ENOENT && (status & Fs_Read)) {
            set_syserrortext(errno);
            {
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         else 

#line 1248 "fsys.r"

            {
            f = fopen(r_tend.d[1].vword.sptr, mode);
            }
         }
      else {

#line 1256 "fsys.r"

         if (S_ISDIR(st.st_mode)) {
            if (status & Fs_Write) 
               {
               err_msg(

#line 1258 "fsys.r"

               173, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }
            else 

#line 1259 "fsys.r"

               {

               f = (FILE *)opendir(r_tend.d[1].vword.sptr);
               status |= Fs_Directory;
               }
            }
         else 

#line 1290 "fsys.r"

            {
            f = fopen(r_tend.d[1].vword.sptr, mode);
            }
         }
      }

#line 1302 "fsys.r"

   if (f == NULL) {
      set_syserrortext(errno);
      {
      tend = r_tend.previous;
      return A_Resume;
      }
      }

   StrLen(r_tend.d[0]) = strlen(r_tend.d[1].vword.sptr);
   StrLoc(r_tend.d[0]) = r_tend.d[1].vword.sptr;

   do {if (((*(struct b_file**)&r_tend.d[2].vword.bptr) = alcfile(f, status, &r_tend.d[0])) == NULL) {
         err_msg(0, NULL);
         tend = r_tend.previous;
         return A_Resume;
         }
      }
   while (0);
   {
   r_args[0].vword.bptr = (union block *)

      (*(struct b_file**)&r_tend.d[2].vword.bptr);
   r_args[0].dword = D_File;
   tend = r_tend.previous;
   return A_Continue;
   }
   }
   }

int Zread (dptr r_args);
FncBlock(read, 1, 0)

int Zread(r_args)
dptr r_args;
   {
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[2];
      } r_tend;

   r_tend.d[1].dword = D_Null;
   r_tend.d[0] = emptystr;
   r_tend.num = 2;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;

#line 1334 "fsys.r"

   if (((r_args[1]).dword == D_Null)) {
      
      r_args[1].dword = D_File;
      BlkLoc(r_args[1]) = (union block *)&k_input;
      }
   else {if (!((r_args[1]).dword == D_File)) {
         {
         err_msg(

#line 1340 "fsys.r"

         105, &(r_args[1]));
         tend = r_tend.previous;
         return A_Resume;
         }
         }
      }
   {
   register word slen, rlen; 

   int status; 
   char sbuf[MaxReadStr]; 

   FILE *fp; 

   SOCKET ws;

#line 1357 "fsys.r"

   k_errornumber = 0;
   IntVal(amperErrno) = 0;

#line 1363 "fsys.r"

   fp = BlkD(r_args[1], File)->fd.fp;
   status = BlkLoc(r_args[1])->File.status;
   if ((status & Fs_Read) == 0) {
      if (status & Fs_Pipe) 
         {
         tend = r_tend.previous;
         return A_Resume;
         }

#line 1367 "fsys.r"

      {
      err_msg(

#line 1367 "fsys.r"

      212, &(r_args[1]));
      tend = r_tend.previous;
      return A_Resume;
      }
      }

#line 1376 "fsys.r"

   if (status & Fs_Socket) {
      StrLen(r_tend.d[1]) = 0;
      do {
         ws = (SOCKET)BlkD(r_args[1], File)->fd.fd;
         DEC_NARTHREADS;
         if ((slen = sock_getstrg(sbuf, MaxReadStr, ws)) == -1) {

            INC_NARTHREADS_CONTROLLED;
            {
            tend = r_tend.previous;
            return A_Resume;
            }
            }

#line 1386 "fsys.r"

         INC_NARTHREADS_CONTROLLED;
         if (slen == -3) {
            tend = r_tend.previous;
            return A_Resume;
            }
         if (slen == 1 && *sbuf == '\n') 
            break;
         rlen = slen < 0 ? (word)MaxReadStr : slen;

         do {if ((reserve(Strings, rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1396 "fsys.r"

         if (StrLen(r_tend.d[1]) > 0 && !InRange(strbase, StrLoc(r_tend.d[1]), strfree)) {
            do {if ((reserve(Strings, StrLen(r_tend.d[1]) + rlen)) == NULL) {
                  err_msg(0, NULL);
                  tend = r_tend.previous;
                  return A_Resume;
                  }
               }
            while (0);

#line 1398 "fsys.r"

            do {if (((StrLoc(r_tend.d[1]) = alcstr(StrLoc(r_tend.d[1]), StrLen(r_tend.d[1])))) == NULL) {
                  err_msg(0, NULL);
                  tend = r_tend.previous;
                  return A_Resume;
                  }
               }
            while (0);
            }

#line 1401 "fsys.r"

         do {if ((r_tend.d[0].vword.sptr = alcstr(sbuf, rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1402 "fsys.r"

         if (StrLen(r_tend.d[1]) == 0) 
            StrLoc(r_tend.d[1]) = r_tend.d[0].vword.sptr;
         StrLen(r_tend.d[1]) += rlen;
         if (StrLoc(r_tend.d[1])[StrLen(r_tend.d[1]) - 1] == '\n') {StrLen(r_tend.d[1])--;break;
            }
         else 

#line 1406 "fsys.r"

            {
            }
         }
      while (
      slen > 0);
      {
      r_args[0] = r_tend.d[1];
      tend = r_tend.previous;
      return A_Continue;
      }
      }

#line 1419 "fsys.r"

   if ((status & Fs_Unbuf) && (!(status & Fs_Messaging))) {
      if (status & Fs_Socket) 
         {
         err_msg(

#line 1421 "fsys.r"

         1048, &(r_args[1]));
         tend = r_tend.previous;
         return A_Resume;
         }

#line 1422 "fsys.r"

      status &= ~Fs_Unbuf;

#line 1427 "fsys.r"

      status |= Fs_Buff;
      BlkLoc(r_args[1])->File.status = status;
      }

#line 1433 "fsys.r"

   if ((status & Fs_Writing) && !(status & Fs_BPipe)) {
      if (fseek(fp, 0L, SEEK_CUR) != 0) {

         set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1439 "fsys.r"

      BlkLoc(r_args[1])->File.status &= ~Fs_Writing;
      }
   BlkLoc(r_args[1])->File.status |= Fs_Reading;

#line 1460 "fsys.r"

   StrLen(r_tend.d[1]) = 0;
   StrLoc(r_tend.d[1]) = "";
   do {

#line 1483 "fsys.r"

      if (status & Fs_Directory) {
         struct dirent *d; 
         char *s, *p = sbuf;
         IntVal(amperErrno) = 0;
         slen = 0;
         DEC_NARTHREADS;
         d = readdir((DIR *)fp);
         INC_NARTHREADS_CONTROLLED;
         if (!d) {
            set_syserrortext(errno);
            {
            tend = r_tend.previous;
            return A_Resume;
            }
            }

#line 1495 "fsys.r"

         s = d->d_name;
         while (*s && slen++ < MaxReadStr) 
            *p++ = *s++;
         if (slen == MaxReadStr) 
            slen = -2;
         }
      else 

#line 1533 "fsys.r"

      if (status & Fs_Pty) {

#line 1537 "fsys.r"

         DEC_NARTHREADS;
         if ((slen = ptgetstr(sbuf, MaxReadStr, (struct ptstruct *)fp, 0)) 
            == -1) {
            INC_NARTHREADS_CONTROLLED;
            set_errortext(214);
            {
            tend = r_tend.previous;
            return A_Resume;
            }
            }

#line 1544 "fsys.r"

         INC_NARTHREADS_CONTROLLED;
         }
      else 

#line 1549 "fsys.r"

      if ((slen = getstrg(sbuf, MaxReadStr, BlkD(r_args[1], File))) == -1) {

         set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1559 "fsys.r"

      if ((status & Fs_Messaging) && (slen == -2)) rlen = MaxReadStr - 1;
      else 
         rlen = slen < 0 ? (word)MaxReadStr : slen;

      do {if ((reserve(Strings, rlen)) == NULL) {
            err_msg(0, NULL);
            tend = r_tend.previous;
            return A_Resume;
            }
         }
      while (0);

#line 1567 "fsys.r"

      if (StrLen(r_tend.d[1]) > 0 && !InRange(strbase, StrLoc(r_tend.d[1]), strfree)) {

#line 1572 "fsys.r"

         do {if ((reserve(Strings, StrLen(r_tend.d[1]) + rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1577 "fsys.r"

         {int i, j;
         r_tend.d[0].vword.sptr = alcstr(NULL, StrLen(r_tend.d[1]) + rlen);
         for (i = 0; i < StrLen(r_tend.d[1]); i++) r_tend.d[0].vword.sptr[i] = StrLoc(r_tend.d[1])[i];
         for (j = 0; j < rlen; j++) r_tend.d[0].vword.sptr[i + j] = sbuf[j];
         StrLoc(r_tend.d[1]) = r_tend.d[0].vword.sptr;
         }
         }
      else 
         do {if ((r_tend.d[0].vword.sptr = alcstr(sbuf, rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1587 "fsys.r"

      if (StrLen(r_tend.d[1]) == 0) 
         StrLoc(r_tend.d[1]) = r_tend.d[0].vword.sptr;
      StrLen(r_tend.d[1]) += rlen;
      }
   while (

#line 1590 "fsys.r"

   slen < 0);
   {
   r_args[0] = 

#line 1591 "fsys.r"

      r_tend.d[1];
   tend = r_tend.previous;
   return A_Continue;
   }
   }
   }

int Zreads (dptr r_args);
FncBlock(reads, 2, 0)

int Zreads(r_args)
dptr r_args;
   {
   C_integer r_i1;
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[2];
      } r_tend;

   r_tend.d[1] = emptystr;
   r_tend.d[0].dword = D_Null;
   r_tend.num = 2;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;

#line 1602 "fsys.r"

   if (((r_args[1]).dword == D_Null)) {
      
      r_args[1].dword = D_File;
      BlkLoc(r_args[1]) = (union block *)&k_input;
      }
   else {if (!((r_args[1]).dword == D_File)) {
         {
         err_msg(

#line 1608 "fsys.r"

         105, &(r_args[1]));
         tend = r_tend.previous;
         return A_Resume;
         }
         }
      }

#line 1613 "fsys.r"

   if (!def_c_int(&(r_args[2]), 1L, &(r_i1))) {
      {
      err_msg(

#line 1614 "fsys.r"

      101, &(r_args[2]));
      tend = r_tend.previous;
      return A_Resume;
      }
      }

   {
   register word slen, rlen; 
   register char *sptr; 
   char sbuf[MaxReadStr]; 
   SOCKET ws; 
   uword bytesread = 0; 
   uword Maxread = 0; 
   long tally, nbytes; 
   int status, fd, kk; 
   FILE *fp = NULL; 

#line 1637 "fsys.r"

   struct stat statbuf;

#line 1642 "fsys.r"

   status = BlkD(r_args[1], File)->status;
   if ((status & Fs_Read) == 0) 
      {
      err_msg(

#line 1644 "fsys.r"

      212, &(r_args[1]));
      tend = r_tend.previous;
      return A_Resume;
      }

#line 1647 "fsys.r"

   if (status & Fs_Messaging) {
      struct MFile *mf = BlkLoc(r_args[1])->File.fd.mf;

#line 1651 "fsys.r"

      Maxread = (unsigned)r_i1 <= MaxReadStr ? r_i1 : MaxReadStr;

      StrLoc(r_tend.d[0]) = NULL;
      StrLen(r_tend.d[0]) = 0;
      if (!MFIN(mf, READING)) {
         Mstartreading(mf);
         }
      nbytes = 0;
      do {
         if (bytesread > 0) {
            if (r_i1 >= 0 && r_i1 - bytesread <= MaxReadStr) 
               Maxread = r_i1 - bytesread;
            else 
               Maxread = MaxReadStr;
            }
         DEC_NARTHREADS;
         slen = tp_read(mf->tp, sbuf, Maxread);
         INC_NARTHREADS_CONTROLLED;

         if (slen <= 0) {
            extern int Merror;
            if (Merror >= 1200) {
               {
               err_msg(

#line 1673 "fsys.r"

               Merror, &(r_args[1]));
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 1675 "fsys.r"

            if (bytesread == 0) 
               {
               tend = r_tend.previous;
               return A_Resume;
               }
            else 
               {
               r_args[0] = 

#line 1677 "fsys.r"

                  r_tend.d[0];
               tend = r_tend.previous;
               return A_Continue;
               }
            }

#line 1679 "fsys.r"

         bytesread += slen;
         rlen = slen < 0 ? (word)MaxReadStr : slen;

         do {if ((reserve(Strings, StrLen(r_tend.d[0]) + rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1683 "fsys.r"

         if (StrLen(r_tend.d[0]) > 0 && !InRange(strbase, StrLoc(r_tend.d[0]), strfree)) {
            do {if (((StrLoc(r_tend.d[0]) = alcstr(StrLoc(r_tend.d[0]), StrLen(r_tend.d[0])))) == NULL) {
                  err_msg(0, NULL);
                  tend = r_tend.previous;
                  return A_Resume;
                  }
               }
            while (0);
            }

#line 1688 "fsys.r"

         do {if ((sptr = alcstr(sbuf, rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1689 "fsys.r"

         if (StrLen(r_tend.d[0]) == 0) 
            StrLoc(r_tend.d[0]) = sptr;
         StrLen(r_tend.d[0]) += rlen;
         }
      while ((r_i1 == -1) || (bytesread < r_i1));
      {
      r_args[0] = r_tend.d[0];
      tend = r_tend.previous;
      return A_Continue;
      }
      }
   else 

   if (status & Fs_Pty) {
      struct ptstruct *p = (struct ptstruct *)BlkLoc(r_args[1])->File.fd.fp;r_tend.d[1].vword.sptr = 
      alcstr(NULL, r_i1);
      DEC_NARTHREADS;
      if ((slen = ptlongread(r_tend.d[1].vword.sptr, r_i1, p)) == -1) {
         INC_NARTHREADS_CONTROLLED;
         set_errortext(214);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1711 "fsys.r"

      INC_NARTHREADS_CONTROLLED;
      {
      r_args[0].vword.sptr = 

#line 1712 "fsys.r"

         r_tend.d[1].vword.sptr;
      r_args[0].dword = 

#line 1712 "fsys.r"

         slen;
      tend = r_tend.previous;
      return A_Continue;
      }
      }
   else 

   if (status & Fs_Socket) {
      StrLen(r_tend.d[0]) = 0;
      Maxread = (r_i1 <= MaxReadStr) ? r_i1 : MaxReadStr;
      do {
         ws = (SOCKET)BlkD(r_args[1], File)->fd.fd;
         if (bytesread > 0) {
            if (r_i1 - bytesread <= MaxReadStr) 
               Maxread = r_i1 - bytesread;
            else 
               Maxread = MaxReadStr;
            }
         DEC_NARTHREADS;
         if ((slen = sock_getstrg(sbuf, Maxread, ws)) == -1) {

            INC_NARTHREADS_CONTROLLED;
            if (bytesread == 0) 
               {
               tend = r_tend.previous;
               return A_Resume;
               }
            else 
               {
               r_args[0] = 

#line 1737 "fsys.r"

                  r_tend.d[0];
               tend = r_tend.previous;
               return A_Continue;
               }
            }

#line 1739 "fsys.r"

         INC_NARTHREADS_CONTROLLED;
         if (slen == -3) {
            tend = r_tend.previous;
            return A_Resume;
            }

         if (slen > 0) 
            bytesread += slen;
         rlen = slen < 0 ? (word)MaxReadStr : slen;

         do {if ((reserve(Strings, StrLen(r_tend.d[0]) + rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1750 "fsys.r"

         if (StrLen(r_tend.d[0]) > 0 && !InRange(strbase, StrLoc(r_tend.d[0]), strfree)) {
            do {if ((reserve(Strings, StrLen(r_tend.d[0]) + rlen)) == NULL) {
                  err_msg(0, NULL);
                  tend = r_tend.previous;
                  return A_Resume;
                  }
               }
            while (0);

#line 1752 "fsys.r"

            do {if (((StrLoc(r_tend.d[0]) = alcstr(StrLoc(r_tend.d[0]), StrLen(r_tend.d[0])))) == NULL) {
                  err_msg(0, NULL);
                  tend = r_tend.previous;
                  return A_Resume;
                  }
               }
            while (0);
            }

#line 1756 "fsys.r"

         do {if ((sptr = alcstr(sbuf, rlen)) == NULL) {
               err_msg(0, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
            }
         while (0);

#line 1757 "fsys.r"

         if (StrLen(r_tend.d[0]) == 0) 
            StrLoc(r_tend.d[0]) = sptr;
         StrLen(r_tend.d[0]) += rlen;
         }
      while (

#line 1760 "fsys.r"

      (r_i1 == -1) || (bytesread < r_i1));
      {
      r_args[0] = 

#line 1761 "fsys.r"

         r_tend.d[0];
      tend = r_tend.previous;
      return A_Continue;
      }
      }

#line 1768 "fsys.r"

   if (strcmp(StrLoc(BlkD(r_args[1], File)->fname), "pipe") != 0) {
      status |= Fs_Buff;
      BlkLoc(r_args[1])->File.status = status;
      }

#line 1774 "fsys.r"

   fp = BlkD(r_args[1], File)->fd.fp;
   if (status & Fs_Writing) {
      fseek(fp, 0L, SEEK_CUR);
      BlkLoc(r_args[1])->File.status &= ~Fs_Writing;
      }
   BlkLoc(r_args[1])->File.status |= Fs_Reading;

#line 1798 "fsys.r"

   if ((BlkD(r_args[1], File)->status & Fs_Directory) != 0) {
      char *sptr; 
      struct dirent *de;
      DEC_NARTHREADS;
      de = readdir((DIR *)fp);
      INC_NARTHREADS_CONTROLLED;
      if (de == NULL) {
         set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1808 "fsys.r"

      nbytes = strlen(de->d_name);
      if (nbytes > r_i1) 
         nbytes = r_i1;
      do {if ((sptr = alcstr(de->d_name, nbytes)) == NULL) {
            err_msg(0, NULL);
            tend = r_tend.previous;
            return A_Resume;
            }
         }
      while (0);
      {
      r_args[0].vword.sptr = 

#line 1812 "fsys.r"

         sptr;
      r_args[0].dword = 

#line 1812 "fsys.r"

         nbytes;
      tend = r_tend.previous;
      return A_Continue;
      }
      }

#line 1820 "fsys.r"

   if ((r_i1 == -1) && ((status & ~Fs_Untrans) == (Fs_Read | Fs_Buff))) {
      if ((fd = fileno(fp)) == -1) {set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1822 "fsys.r"

      if ((kk = fstat(fd, &statbuf)) == -1) {set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1823 "fsys.r"

      r_i1 = statbuf.st_size;
      }
   else 

#line 1828 "fsys.r"

   if ((r_i1 >= 65535) && ((status & ~Fs_Untrans) == (Fs_Read | Fs_Buff))) {
      if ((fd = fileno(fp)) == -1) {set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1830 "fsys.r"

      if ((kk = fstat(fd, &statbuf)) == -1) {set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1831 "fsys.r"

      if (r_i1 > statbuf.st_size) r_i1 = statbuf.st_size;
      }
   else 

#line 1836 "fsys.r"

   if (r_i1 <= 0) {
      irunerr(205, r_i1);
      {
      tend = r_tend.previous;
      return A_Resume;
      }
      }
   if ((status & Fs_Unbuf) && !(status & Fs_BPipe)) {

#line 1846 "fsys.r"

      int fd;

      if ((fd = get_fd(r_args[1], 0)) < 0) 
         {
         err_msg(

#line 1849 "fsys.r"

         174, &(r_args[1]));
         tend = r_tend.previous;
         return A_Resume;
         }

#line 1851 "fsys.r"

      IntVal(amperErrno) = 0;
      DEC_NARTHREADS;
      if (u_read(fd, r_i1, status, &r_tend.d[0]) == 0) {
         INC_NARTHREADS_CONTROLLED;
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }

#line 1857 "fsys.r"

      INC_NARTHREADS_CONTROLLED;
      {
      r_args[0] = 

#line 1858 "fsys.r"

         r_tend.d[0];
      tend = r_tend.previous;
      return A_Continue;
      }
      }

#line 1865 "fsys.r"

   do {if ((StrLoc(r_tend.d[0]) = alcstr(NULL, r_i1)) == NULL) {
         err_msg(0, NULL);
         tend = r_tend.previous;
         return A_Resume;
         }
      }
   while (0);

#line 1866 "fsys.r"

   StrLen(r_tend.d[0]) = 0;

#line 1905 "fsys.r"

   DEC_NARTHREADS;
   tally = longread(StrLoc(r_tend.d[0]), sizeof(char), r_i1, fp);
   INC_NARTHREADS_CONTROLLED;

#line 1912 "fsys.r"

   if (tally == 0) 
      {
      tend = r_tend.previous;
      return A_Resume;
      }

#line 1914 "fsys.r"

   StrLen(r_tend.d[0]) = tally;

#line 1918 "fsys.r"

   nbytes = (word)((StrLoc(r_tend.d[0]) + tally) - (strfree));
   EVStrAlc(nbytes);
   strtotal += nbytes;
   strfree = StrLoc(r_tend.d[0]) + tally;
   {
   r_args[0] = 

#line 1922 "fsys.r"

      r_tend.d[0];
   tend = r_tend.previous;
   return A_Continue;
   }
   }
   }

int Zremove (dptr r_args);
FncBlock(remove, 1, 0)

int Zremove(r_args)
dptr r_args;
   {

   if (!cnv_c_str(&(r_args[1]), &(r_args[1]))) {
      {
      err_msg(

#line 1935 "fsys.r"

      103, &(r_args[1]));
      return A_Resume;
      }
      }

   {

   CURTSTATE();

   if (remove(r_args[1].vword.sptr) != 0) {

      IntVal(amperErrno) = 0;

#line 1950 "fsys.r"

      if (rmdir(r_args[1].vword.sptr) == 0) 
         {
         r_args[0] = 

#line 1950 "fsys.r"

            nulldesc;
         return A_Continue;
         }

#line 1952 "fsys.r"

      set_syserrortext(errno);
      return A_Resume;
      }
   {
   r_args[0] = 

#line 1955 "fsys.r"

      nulldesc;
   return A_Continue;
   }
   }
   }

int Zrename (dptr r_args);
FncBlock(rename, 2, 0)

int Zrename(r_args)
dptr r_args;
   {

#line 1967 "fsys.r"

   if (!cnv_c_str(&(r_args[1]), &(r_args[1]))) {
      {
      err_msg(

#line 1968 "fsys.r"

      103, &(r_args[1]));
      return A_Resume;
      }
      }

#line 1969 "fsys.r"

   if (!cnv_c_str(&(r_args[2]), &(r_args[2]))) {
      {
      err_msg(

#line 1970 "fsys.r"

      103, &(r_args[2]));
      return A_Resume;
      }
      }

#line 1976 "fsys.r"

   {
   if (rename(r_args[1].vword.sptr, r_args[2].vword.sptr) == 0) 
      {
      r_args[0] = 

#line 1977 "fsys.r"

         nulldesc;
      return A_Continue;
      }

#line 1983 "fsys.r"

   set_syserrortext(errno);
   return A_Resume;
   }
   }

int Zseek (dptr r_args);
FncBlock(seek, 2, 0)

int Zseek(r_args)
dptr r_args;
   {
   C_integer r_i1;

#line 2040 "fsys.r"

   if (!((r_args[1]).dword == D_File)) {
      {
      err_msg(

#line 2041 "fsys.r"

      105, &(r_args[1]));
      return A_Resume;
      }
      }

   if (!def_c_int(&(r_args[2]), 1L, &(r_i1))) {
      {
      err_msg(

#line 2047 "fsys.r"

      0, NULL);
      return A_Resume;
      }
      }

#line 2053 "fsys.r"

   {
   FILE *fd;

#line 2059 "fsys.r"

   fd = BlkD(r_args[1], File)->fd.fp;
   if (BlkLoc(r_args[1])->File.status == 0) {
      set_errortext(214);
      return A_Resume;
      }

#line 2066 "fsys.r"

   if (BlkLoc(r_args[1])->File.status & Fs_Directory) {
      set_errortext(174);
      return A_Resume;
      }

#line 2097 "fsys.r"

   if (r_i1 > 0) {

#line 2102 "fsys.r"

      if (fseek(fd, r_i1 - 1, SEEK_SET) == -1) {

         set_syserrortext(errno);
         return A_Resume;
         }
      }
   else 

      {

#line 2130 "fsys.r"

      if (fseek(fd, r_i1, SEEK_END) == -1) {
         set_syserrortext(errno);
         return A_Resume;
         }
      }

#line 2137 "fsys.r"

   BlkLoc(r_args[1])->File.status &= ~(Fs_Reading | Fs_Writing);
   {
   r_args[0] = 

#line 2138 "fsys.r"

      r_args[1];
   return A_Continue;
   }
   }
   }

int Zsystem (dptr r_args);
FncBlock(system, 5, 0)

int Zsystem(r_args)
dptr r_args;
   {
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[4];
      } r_tend;

   r_tend.d[3] = emptystr;
   r_tend.d[2] = emptystr;
   r_tend.d[1] = emptystr;
   r_tend.d[0] = nullptr;
   r_tend.num = 4;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;

#line 2147 "fsys.r"

   if (!((r_args[2]).dword == D_File)) {
      if (!(!((r_args[2]).dword & F_Nqual))) {
         if (!((r_args[2]).dword == D_Null)) {
            {
            err_msg(

#line 2150 "fsys.r"

            105, &(r_args[2]));
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         }
      }

#line 2151 "fsys.r"

   if (!((r_args[3]).dword == D_File)) {
      if (!(!((r_args[3]).dword & F_Nqual))) {
         if (!((r_args[3]).dword == D_Null)) {
            {
            err_msg(

#line 2154 "fsys.r"

            105, &(r_args[3]));
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         }
      }

#line 2155 "fsys.r"

   if (!((r_args[4]).dword == D_File)) {
      if (!(!((r_args[4]).dword & F_Nqual))) {
         if (!((r_args[4]).dword == D_Null)) {
            {
            err_msg(

#line 2158 "fsys.r"

            105, &(r_args[4]));
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         }
      }

#line 2159 "fsys.r"

   if (!((r_args[1]).dword == D_List)) {
      if (!(!((r_args[1]).dword & F_Nqual))) {
         {
         err_msg(

#line 2161 "fsys.r"

         110, &(r_args[1]));
         tend = r_tend.previous;
         return A_Resume;
         }
         }
      }

#line 2162 "fsys.r"

   if (!(!((r_args[5]).dword & F_Nqual))) {
      if (!
#ifdef LargeInts
         (((

#line 2163 "fsys.r"

         r_args[5]).dword == D_Integer) || ((r_args[5]).dword == D_Lrgint))
#else					/* LargeInts */
         ((

#line 2163 "fsys.r"

         r_args[5]).dword == D_Integer)
#endif					/* LargeInts */
      ) {

#line 2164 "fsys.r"

         if (!((r_args[5]).dword == D_File)) {
            if (!((r_args[5]).dword == D_Null)) {
               {
               err_msg(

#line 2166 "fsys.r"

               170, &(r_args[5]));
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }
         }
      }

#line 2170 "fsys.r"

   {

   int pid; 

   int i, j, n, is_argv_str = 0; 
   C_integer i_mode = 0; 

#line 2184 "fsys.r"

   char **margv = NULL;
   IntVal(amperErrno) = 0;

#line 2188 "fsys.r"

   if (
#ifdef LargeInts
      (((

#line 2188 "fsys.r"

      r_args[5]).dword == D_Integer) || ((r_args[5]).dword == D_Lrgint))
#else					/* LargeInts */
      ((

#line 2188 "fsys.r"

      r_args[5]).dword == D_Integer)
#endif					/* LargeInts */
   ) 

#line 2188 "fsys.r"

      {
      if (!cnv_c_int(&(r_args[5]), &(i_mode))) {
         err_msg(

#line 2189 "fsys.r"

         101, &(r_args[5]));
         tend = r_tend.previous;
         return A_Resume;
         }
      }
   else 

#line 2191 "fsys.r"

   if ((!((r_args[5]).dword & F_Nqual))) {

      if (!cnv_c_str(&(r_args[5]), &(r_tend.d[3]))) {
         err_msg(

#line 2193 "fsys.r"

         103, &(r_args[5]));
         tend = r_tend.previous;
         return A_Resume;
         }

#line 2194 "fsys.r"

      i_mode = (strcmp(r_tend.d[3].vword.sptr, "nowait") == 0);
      }

   if (((r_args[1]).dword == D_List)) {
      margv = (char **)malloc((BlkD(r_args[1], List)->size + 3) * sizeof(char *));
      if (margv == NULL) {
         err_msg(

#line 2199 "fsys.r"

         305, NULL);
         tend = r_tend.previous;
         return A_Resume;
         }

#line 2200 "fsys.r"

      n = 0;

      for (r_tend.d[0].vword.bptr = BlkD(r_args[1], List)->listhead; BlkType(r_tend.d[0].vword.bptr) == T_Lelem; 
      r_tend.d[0].vword.bptr = Blk(r_tend.d[0].vword.bptr, Lelem)->listnext) {
         for (i = 0; i < Blk(r_tend.d[0].vword.bptr, Lelem)->nused; i++) {
            dptr f;
            j = Blk(r_tend.d[0].vword.bptr, Lelem)->first + i;
            if (j >= Blk(r_tend.d[0].vword.bptr, Lelem)->nslots) 
               j -= Blk(r_tend.d[0].vword.bptr, Lelem)->nslots;
            f = &Blk(r_tend.d[0].vword.bptr, Lelem)->lslots[j];

            if (!cnv_c_str(&((*f)), &(r_tend.d[1]))) 
               {
               err_msg(

#line 2212 "fsys.r"

               103, &(*f));
               tend = r_tend.previous;
               return A_Resume;
               }

#line 2223 "fsys.r"

            margv[n++] = r_tend.d[1].vword.sptr;
            }
         }

#line 2228 "fsys.r"

      margv[n] = 0;
      }
   else if ((!((r_args[1]).dword & F_Nqual))) {
      is_argv_str = 1;
      cnv_c_str(&(r_args[1]), &(r_tend.d[2]));

      {
      char *s = r_tend.d[2].vword.sptr;

#line 2245 "fsys.r"

      while ((s = strstr(s, ">")) != NULL) {

#line 2249 "fsys.r"

         if (((s - r_tend.d[2].vword.sptr > 0) && s[-1] == '&') || (s[1] == '&')) {

            if ((s - r_tend.d[2].vword.sptr > 0) && s[-1] == '&') {
               s[-1] = '\0';
               s++;
               }
            else {
               *s = '\0';
               s += 2;
               }

            while (*s == ' ') s++;
            StrLoc(r_args[3]) = StrLoc(r_args[4]) = s;
            while (*s) {
               if (*s == ' ') {
                  *s++ = '\0';
                  break;
                  }
               s++;
               }
            StrLen(r_args[3]) = StrLen(r_args[4]) = strlen(StrLoc(r_args[3]));
            }
         else if ((s - r_tend.d[2].vword.sptr > 0) && s[-1] == '2') {
            s[-1] = '\0';
            s++;
            while (*s == ' ') s++;
            StrLoc(r_args[4]) = s;
            while (*s) {
               if (*s == ' ') {
                  *s++ = '\0';
                  break;
                  }
               s++;
               }
            StrLen(r_args[4]) = strlen(StrLoc(r_args[4]));
            if (!strcmp(StrLoc(r_args[4]), "&1")) {
               r_args[4] = r_args[3];
               }
            }
         else if (s[1] == '>') {
            *s = '\0';
            s += 2;
            while (*s == ' ') s++;
            StrLoc(r_args[3]) = s;
            while (*s) {
               if (*s == ' ') {
                  *s++ = '\0';
                  break;
                  }
               s++;
               }
            StrLen(r_args[3]) = strlen(StrLoc(r_args[3]));

            r_args[3].dword = D_Integer;
            r_args[3].vword.integr = 

            open(StrLoc(r_args[3]), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            }
         else 

#line 2311 "fsys.r"

            {
            *s = '\0';
            s++;
            while (*s == ' ') s++;
            StrLoc(r_args[3]) = s;
            while (*s) {
               if (*s == ' ') {
                  *s++ = '\0';
                  break;
                  }
               s++;
               }
            StrLen(r_args[3]) = strlen(StrLoc(r_args[3]));
            }
         }
      }
      }

#line 2334 "fsys.r"

   if ((!((r_args[2]).dword & F_Nqual))) {

      cnv_c_str(&(r_args[2]), &(r_tend.d[3]));
      r_args[2].dword = D_Integer;
      r_args[2].vword.integr = open(r_tend.d[3].vword.sptr, O_RDONLY);
      }
   if ((!((r_args[3]).dword & F_Nqual)) && (!((r_args[4]).dword & F_Nqual)) && 
      (StrLen(r_args[3]) == StrLen(r_args[4])) && 
      !strncmp(StrLoc(r_args[3]), StrLoc(r_args[4]), StrLen(r_args[3]))) {

#line 2345 "fsys.r"

      cnv_c_str(&(r_args[3]), &(r_tend.d[3]));
      r_args[3].dword = r_args[4].dword = D_Integer;
      r_args[3].vword.integr = 

      open(r_tend.d[3].vword.sptr, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

#line 2355 "fsys.r"

      r_args[4].vword.integr = r_args[3].vword.integr;
      }
   else {
      if ((!((r_args[3]).dword & F_Nqual))) {

         cnv_c_str(&(r_args[3]), &(r_tend.d[3]));
         r_args[3].dword = D_Integer;
         r_args[3].vword.integr = 

         open(r_tend.d[3].vword.sptr, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
         }

#line 2370 "fsys.r"

      if ((!((r_args[4]).dword & F_Nqual))) {

         cnv_c_str(&(r_args[4]), &(r_tend.d[3]));
         r_args[4].dword = D_Integer;
         r_args[4].vword.integr = 

         open(r_tend.d[3].vword.sptr, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
         }
      }

#line 2390 "fsys.r"

   switch (pid = vfork()) {

#line 2394 "fsys.r"

      case 0: 

         dup_fds(&r_args[2], &r_args[3], &r_args[4]);

         if (is_argv_str) {
            execl("/bin/sh", "sh", "-c", r_tend.d[2].vword.sptr, (char *)0);
            }
         else {
            if (execvp(margv[0], margv) == -1) {
               free(margv);
               }
            }

#line 2412 "fsys.r"

         IntVal(amperErrno) = errno;
         {
         err_msg(

#line 2413 "fsys.r"

         500, NULL);
         tend = r_tend.previous;
         return A_Resume;
         }

#line 2414 "fsys.r"

         break;
      case -1: 
         if (margv) free(margv);
         set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }

#line 2419 "fsys.r"

         break;
      default: 

#line 2423 "fsys.r"

         if (!((r_args[2]).dword == D_Null) && ((r_args[2]).dword == D_File)) {
            if (BlkD(r_args[2], File)->status & Fs_BPipe) 
               push_filepid(pid, BlkD(r_args[2], File)->fd.fp, Fs_BPipe);
            }

         if (!((r_args[3]).dword == D_Null) && ((r_args[3]).dword == D_File)) {
            if (BlkD(r_args[3], File)->status & Fs_BPipe) 
               push_filepid(pid, BlkD(r_args[3], File)->fd.fp, Fs_BPipe);
            }

#line 2434 "fsys.r"

         if (margv) free(margv);
         if (
#ifdef LargeInts
            (((

#line 2435 "fsys.r"

            r_args[2]).dword == D_Integer) || ((r_args[2]).dword == D_Lrgint))
#else					/* LargeInts */
            ((

#line 2435 "fsys.r"

            r_args[2]).dword == D_Integer)
#endif					/* LargeInts */
             

#line 2435 "fsys.r"

            && IntVal(r_args[2]) > -1) close(IntVal(r_args[2]));
         if (
#ifdef LargeInts
            (((

#line 2436 "fsys.r"

            r_args[3]).dword == D_Integer) || ((r_args[3]).dword == D_Lrgint))
#else					/* LargeInts */
            ((

#line 2436 "fsys.r"

            r_args[3]).dword == D_Integer)
#endif					/* LargeInts */
             

#line 2436 "fsys.r"

            && IntVal(r_args[3]) > -1) close(IntVal(r_args[3]));
         if (
#ifdef LargeInts
            (((

#line 2437 "fsys.r"

            r_args[4]).dword == D_Integer) || ((r_args[4]).dword == D_Lrgint))
#else					/* LargeInts */
            ((

#line 2437 "fsys.r"

            r_args[4]).dword == D_Integer)
#endif					/* LargeInts */
             

#line 2437 "fsys.r"

            && (IntVal(r_args[4]) > -1) && 
            ((!
#ifdef LargeInts
            (((

#line 2438 "fsys.r"

            r_args[3]).dword == D_Integer) || ((r_args[3]).dword == D_Lrgint))
#else					/* LargeInts */
            ((

#line 2438 "fsys.r"

            r_args[3]).dword == D_Integer)
#endif					/* LargeInts */
            ) 

#line 2438 "fsys.r"

            || (IntVal(r_args[3]) != IntVal(r_args[4])))) 
            close(IntVal(r_args[4]));
         if (!i_mode) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) 
               {
               r_args[0].vword.integr = 

#line 2444 "fsys.r"

                  WEXITSTATUS(status);
               r_args[0].dword = D_Integer;
               tend = r_tend.previous;
               return A_Continue;
               }
            else 
               {
               r_args[0].vword.integr = 

#line 2446 "fsys.r"

                  status;
               r_args[0].dword = D_Integer;
               tend = r_tend.previous;
               return A_Continue;
               }
            }
         else 

#line 2449 "fsys.r"

            {
            r_args[0].vword.integr = pid;
            r_args[0].dword = D_Integer;
            tend = r_tend.previous;
            return A_Continue;
            }
         }
   {
   r_args[0] = 

#line 2546 "fsys.r"

      nulldesc;
   tend = r_tend.previous;
   return A_Continue;
   }
   }
   }

int Zwhere (dptr r_args);
FncBlock(where, 1, 0)

int Zwhere(r_args)
dptr r_args;
   {

#line 2611 "fsys.r"

   if (!((r_args[1]).dword == D_File)) {
      {
      err_msg(

#line 2612 "fsys.r"

      105, &(r_args[1]));
      return A_Resume;
      }
      }

#line 2618 "fsys.r"

   {
   FILE *fd; 
   long ftell(); 
   long pos;

#line 2626 "fsys.r"

   fd = BlkD(r_args[1], File)->fd.fp;

   if (BlkLoc(r_args[1])->File.status == 0) {
      set_errortext(212);
      return A_Resume;
      }

#line 2634 "fsys.r"

   if ((BlkLoc(r_args[1])->File.status & Fs_Directory) != 0) {
      set_errortext(174);
      return A_Resume;
      }

#line 2649 "fsys.r"

   pos = ftell(fd) + 1;
   if (pos == 0) {
      set_syserrortext(errno);
      return A_Resume;
      }
   {
   r_args[0].vword.integr = pos;
   r_args[0].dword = D_Integer;
   return A_Continue;
   }
   }
   }

int Zstop (int r_nargs, dptr r_args);
FncBlock(stop, -1, 0)

int Zstop(r_nargs, r_args)
int r_nargs;
dptr r_args;
   {

#line 2868 "fsys.r"

   union f f;

#line 2872 "fsys.r"

   word status = 

#line 2875 "fsys.r"

   k_errout.status;
   char r_sbuf[1][MaxCvtLen];
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[2];
      } r_tend;

   r_tend.d[1].dword = D_Null;
   r_tend.d[0].dword = F_Ptr | F_Nqual;
   r_tend.d[0].vword.bptr = (union block *)

#line 2870 "fsys.r"

      NULL;
   r_tend.num = 2;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;
   switch (

#line 2895 "fsys.r"

   (r_nargs - 0)) {
      case 0:{

#line 2668 "fsys.r"

         {

#line 2671 "fsys.r"

         (*(struct b_file**)&r_tend.d[0].vword.bptr) = &k_errout;
         MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 2675 "fsys.r"

         if ((k_errout.status & Fs_Write) == 0) {
            MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
            {
            err_msg(

#line 2677 "fsys.r"

            213, NULL);
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         else 

#line 2679 "fsys.r"

            {

            f.fp = k_errout.fd.fp;
            }
         }

#line 2903 "fsys.r"

         {

#line 2726 "fsys.r"

         if (status & Fs_Pty) {
            ptputc('\n', f.pt);
            }
         else 

#line 2741 "fsys.r"

         if (status & Fs_Messaging) {
            struct MFile *mf = f.mf; 
            extern int Merror;
            if (!MFIN(mf, WRITING)) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2746 "fsys.r"

               213, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 2748 "fsys.r"

            if (tp_write(mf->tp, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

               syserr("tp_write failed in stop()");
               }

#line 2758 "fsys.r"

            if (Merror != 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2760 "fsys.r"

               Merror, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }
         else if (status & Fs_Socket) {
            if (sock_write(f.fd, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

               syserr("sock_write failed in stop()");
               }
            }
         else 

#line 2779 "fsys.r"

            putc('\n', f.fp);

#line 2787 "fsys.r"

         if (!(status & Fs_Messaging)) {

#line 2793 "fsys.r"

            if (!(status & Fs_Pty)) {

#line 2797 "fsys.r"

               if (!(status & Fs_Socket)) {

#line 2818 "fsys.r"

                  if (ferror(f.fp)) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 2820 "fsys.r"

                     214, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }

#line 2822 "fsys.r"

                  fflush(f.fp);
                  }
               }
            }

#line 2839 "fsys.r"

         MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

         c_exit(EXIT_FAILURE);
         {
         r_args[0] = nulldesc;
         tend = r_tend.previous;
         return A_Continue;
         }
         }}
      default:

#line 2911 "fsys.r"

         {

#line 2920 "fsys.r"

         if (!(((&r_args[1])[0]).dword == D_File)) {

#line 2668 "fsys.r"

            

#line 2671 "fsys.r"

            (*(struct b_file**)&r_tend.d[0].vword.bptr) = &k_errout;
            MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 2675 "fsys.r"

            if ((k_errout.status & Fs_Write) == 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2677 "fsys.r"

               213, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            else 

#line 2679 "fsys.r"

               {

               f.fp = k_errout.fd.fp;
               }
            }

#line 2923 "fsys.r"

         { 

         register word n;

#line 2930 "fsys.r"

         for (n = 0; n < (r_nargs - 0); n++) {
            if ((((&r_args[1])[n]).dword == D_File)) {

#line 2938 "fsys.r"

               if (n > 0) {

#line 2961 "fsys.r"

                  if (status & Fs_Pty) {
                     ptputc('\n', f.pt);
                     }
                  else 

#line 2984 "fsys.r"

                  if (status & Fs_Messaging) {
                     struct MFile *mf = f.mf; 
                     extern int Merror;
                     if (!MFIN(mf, WRITING)) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                        {
                        err_msg(

#line 2992 "fsys.r"

                        213, NULL);
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }

#line 2994 "fsys.r"

                     if (tp_write(mf->tp, "\n", 1) < 0) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 3000 "fsys.r"

                        syserr("tp_write failed in stop()");
                        }

#line 3006 "fsys.r"

                     if (Merror != 0) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                        {
                        err_msg(

#line 3011 "fsys.r"

                        Merror, &((&r_args[1])[n]));
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }
                     }
                  else if (status & Fs_Socket) {
                     if (sock_write(f.fd, "\n", 1) < 0) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 3024 "fsys.r"

                        syserr("sock_write failed in stop()");
                        }
                     }
                  else 

#line 3031 "fsys.r"

                     {

                     putc('\n', f.fp);
                     if (ferror(f.fp)) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                        {
                        err_msg(

#line 3039 "fsys.r"

                        214, NULL);
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }

#line 3041 "fsys.r"

                     fflush(f.fp);
                     }

#line 3049 "fsys.r"

                  if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                  }

#line 3059 "fsys.r"

               status = BlkD((&r_args[1])[n], File)->status;
               if ((status & Fs_Write) == 0) {

                  if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                  {
                  err_msg(

#line 3065 "fsys.r"

                  213, &((&r_args[1])[n]));
                  tend = r_tend.previous;
                  return A_Resume;
                  }
                  }

#line 3067 "fsys.r"

               f.fp = BlkLoc((&r_args[1])[n])->File.fd.fp;

               (*(struct b_file**)&r_tend.d[0].vword.bptr) = BlkD((&r_args[1])[n], File);
               MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               }
            else 

#line 3081 "fsys.r"

               {

#line 3086 "fsys.r"

               if (!def_tstr(r_sbuf[0], &((&r_args[1])[n]), &(emptystr), &(r_tend.d[1]))) {
                  MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                  {
                  err_msg(

#line 3088 "fsys.r"

                  109, &((&r_args[1])[n]));
                  tend = r_tend.previous;
                  return A_Resume;
                  }
                  }

#line 3101 "fsys.r"

               if (status & Fs_Pty) 
                  ptputstr(f.pt, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1]));
               else 

#line 3118 "fsys.r"

               if (status & Fs_Messaging) {
                  struct MFile *mf = f.mf; 
                  extern int Merror;
                  Merror = 0;
                  tp_write(mf->tp, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1]));
                  if (Merror > 1200) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 3125 "fsys.r"

                     Merror, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               else 
               if (status & Fs_Socket) {

                  if (sock_write(f.fd, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1])) < 0) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                     syserr("sock_write failed in stop()");
                     }
                  }
               else 

#line 3143 "fsys.r"

                  {

                  if (putstr(f.fp, &r_tend.d[1]) == Failed) 
                     {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 3148 "fsys.r"

                     214, &((&r_args[1])[n]));
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               }
            }

#line 2726 "fsys.r"

         if (status & Fs_Pty) {
            ptputc('\n', f.pt);
            }
         else 

#line 2741 "fsys.r"

         if (status & Fs_Messaging) {
            struct MFile *mf = f.mf; 
            extern int Merror;
            if (!MFIN(mf, WRITING)) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2746 "fsys.r"

               213, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 2748 "fsys.r"

            if (tp_write(mf->tp, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

               syserr("tp_write failed in stop()");
               }

#line 2758 "fsys.r"

            if (Merror != 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2760 "fsys.r"

               Merror, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }
         else if (status & Fs_Socket) {
            if (sock_write(f.fd, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

               syserr("sock_write failed in stop()");
               }
            }
         else 

#line 2779 "fsys.r"

            putc('\n', f.fp);

#line 2787 "fsys.r"

         if (!(status & Fs_Messaging)) {

#line 2793 "fsys.r"

            if (!(status & Fs_Pty)) {

#line 2797 "fsys.r"

               if (!(status & Fs_Socket)) {

#line 2818 "fsys.r"

                  if (ferror(f.fp)) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 2820 "fsys.r"

                     214, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }

#line 2822 "fsys.r"

                  fflush(f.fp);
                  }
               }
            }

#line 2839 "fsys.r"

         MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

         c_exit(EXIT_FAILURE);
         {
         r_args[0] = (&r_args[1])[n - 1];
         tend = r_tend.previous;
         return A_Continue;
         }
         }}
      }
   }

int Zwrite (int r_nargs, dptr r_args);
FncBlock(write, -1, 0)

int Zwrite(r_nargs, r_args)
int r_nargs;
dptr r_args;
   {

#line 2868 "fsys.r"

   union f f;

#line 2872 "fsys.r"

   word status = 

#line 2881 "fsys.r"

   k_output.status;
   char r_sbuf[1][MaxCvtLen];
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[2];
      } r_tend;

   r_tend.d[1].dword = D_Null;
   r_tend.d[0].dword = F_Ptr | F_Nqual;
   r_tend.d[0].vword.bptr = (union block *)

#line 2870 "fsys.r"

      NULL;
   r_tend.num = 2;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;
   switch (

#line 2895 "fsys.r"

   (r_nargs - 0)) {
      case 0:{

#line 2668 "fsys.r"

         {

#line 2688 "fsys.r"

         (*(struct b_file**)&r_tend.d[0].vword.bptr) = &k_output;
         MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

         if ((k_output.status & Fs_Write) == 0) {
            MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
            {
            err_msg(

#line 2693 "fsys.r"

            213, NULL);
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         else 

#line 2695 "fsys.r"

            {

            f.fp = k_output.fd.fp;
            }
         }

#line 2903 "fsys.r"

         {

#line 2726 "fsys.r"

         if (status & Fs_Pty) {
            ptputc('\n', f.pt);
            }
         else 

#line 2741 "fsys.r"

         if (status & Fs_Messaging) {
            struct MFile *mf = f.mf; 
            extern int Merror;
            if (!MFIN(mf, WRITING)) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2746 "fsys.r"

               213, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 2748 "fsys.r"

            if (tp_write(mf->tp, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 2754 "fsys.r"

               set_errortext(214);
               {
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 2758 "fsys.r"

            if (Merror != 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2760 "fsys.r"

               Merror, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }
         else if (status & Fs_Socket) {
            if (sock_write(f.fd, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 2772 "fsys.r"

               set_syserrortext(errno);
               {
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }
         else putc('\n', f.fp);

#line 2787 "fsys.r"

         if (!(status & Fs_Messaging)) {

#line 2793 "fsys.r"

            if (!(status & Fs_Pty)) {

#line 2797 "fsys.r"

               if (!(status & Fs_Socket)) {

#line 2818 "fsys.r"

                  if (ferror(f.fp)) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 2820 "fsys.r"

                     214, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }

#line 2822 "fsys.r"

                  fflush(f.fp);
                  }
               }
            }

#line 2839 "fsys.r"

         MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
         {
         r_args[0] = 

#line 2846 "fsys.r"

            nulldesc;
         tend = r_tend.previous;
         return A_Continue;
         }
         }}
      default:

#line 2911 "fsys.r"

         {

#line 2920 "fsys.r"

         if (!(((&r_args[1])[0]).dword == D_File)) {

#line 2668 "fsys.r"

            

#line 2688 "fsys.r"

            (*(struct b_file**)&r_tend.d[0].vword.bptr) = &k_output;
            MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

            if ((k_output.status & Fs_Write) == 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2693 "fsys.r"

               213, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            else 

#line 2695 "fsys.r"

               {

               f.fp = k_output.fd.fp;
               }
            }

#line 2923 "fsys.r"

         { 

         register word n;

#line 2930 "fsys.r"

         for (n = 0; n < (r_nargs - 0); n++) {
            if ((((&r_args[1])[n]).dword == D_File)) {

#line 2938 "fsys.r"

               if (n > 0) {

#line 2961 "fsys.r"

                  if (status & Fs_Pty) {
                     ptputc('\n', f.pt);
                     }
                  else 

#line 2984 "fsys.r"

                  if (status & Fs_Messaging) {
                     struct MFile *mf = f.mf; 
                     extern int Merror;
                     if (!MFIN(mf, WRITING)) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                        {
                        err_msg(

#line 2992 "fsys.r"

                        213, NULL);
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }

#line 2994 "fsys.r"

                     if (tp_write(mf->tp, "\n", 1) < 0) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 3002 "fsys.r"

                        set_errortext(214);
                        {
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }

#line 3006 "fsys.r"

                     if (Merror != 0) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                        {
                        err_msg(

#line 3011 "fsys.r"

                        Merror, &((&r_args[1])[n]));
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }
                     }
                  else if (status & Fs_Socket) {
                     if (sock_write(f.fd, "\n", 1) < 0) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 3026 "fsys.r"

                        set_syserrortext(errno);
                        {
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }
                     }
                  else 

#line 3031 "fsys.r"

                     {

                     putc('\n', f.fp);
                     if (ferror(f.fp)) {

                        if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                           MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                        {
                        err_msg(

#line 3039 "fsys.r"

                        214, NULL);
                        tend = r_tend.previous;
                        return A_Resume;
                        }
                        }

#line 3041 "fsys.r"

                     fflush(f.fp);
                     }

#line 3049 "fsys.r"

                  if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                  }

#line 3059 "fsys.r"

               status = BlkD((&r_args[1])[n], File)->status;
               if ((status & Fs_Write) == 0) {

                  if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                  {
                  err_msg(

#line 3065 "fsys.r"

                  213, &((&r_args[1])[n]));
                  tend = r_tend.previous;
                  return A_Resume;
                  }
                  }

#line 3067 "fsys.r"

               f.fp = BlkLoc((&r_args[1])[n])->File.fd.fp;

               (*(struct b_file**)&r_tend.d[0].vword.bptr) = BlkD((&r_args[1])[n], File);
               MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               }
            else 

#line 3081 "fsys.r"

               {

#line 3086 "fsys.r"

               if (!def_tstr(r_sbuf[0], &((&r_args[1])[n]), &(emptystr), &(r_tend.d[1]))) {
                  MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                  {
                  err_msg(

#line 3088 "fsys.r"

                  109, &((&r_args[1])[n]));
                  tend = r_tend.previous;
                  return A_Resume;
                  }
                  }

#line 3101 "fsys.r"

               if (status & Fs_Pty) 
                  ptputstr(f.pt, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1]));
               else 

#line 3118 "fsys.r"

               if (status & Fs_Messaging) {
                  struct MFile *mf = f.mf; 
                  extern int Merror;
                  Merror = 0;
                  tp_write(mf->tp, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1]));
                  if (Merror > 1200) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 3125 "fsys.r"

                     Merror, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               else 
               if (status & Fs_Socket) {

                  if (sock_write(f.fd, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1])) < 0) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 3139 "fsys.r"

                     set_syserrortext(errno);
                     {
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               else 

#line 3143 "fsys.r"

                  {

                  if (putstr(f.fp, &r_tend.d[1]) == Failed) 
                     {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 3148 "fsys.r"

                     214, &((&r_args[1])[n]));
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               }
            }

#line 2726 "fsys.r"

         if (status & Fs_Pty) {
            ptputc('\n', f.pt);
            }
         else 

#line 2741 "fsys.r"

         if (status & Fs_Messaging) {
            struct MFile *mf = f.mf; 
            extern int Merror;
            if (!MFIN(mf, WRITING)) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2746 "fsys.r"

               213, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 2748 "fsys.r"

            if (tp_write(mf->tp, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 2754 "fsys.r"

               set_errortext(214);
               {
               tend = r_tend.previous;
               return A_Resume;
               }
               }

#line 2758 "fsys.r"

            if (Merror != 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2760 "fsys.r"

               Merror, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }
         else if (status & Fs_Socket) {
            if (sock_write(f.fd, "\n", 1) < 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 2772 "fsys.r"

               set_syserrortext(errno);
               {
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            }
         else putc('\n', f.fp);

#line 2787 "fsys.r"

         if (!(status & Fs_Messaging)) {

#line 2793 "fsys.r"

            if (!(status & Fs_Pty)) {

#line 2797 "fsys.r"

               if (!(status & Fs_Socket)) {

#line 2818 "fsys.r"

                  if (ferror(f.fp)) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 2820 "fsys.r"

                     214, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }

#line 2822 "fsys.r"

                  fflush(f.fp);
                  }
               }
            }

#line 2839 "fsys.r"

         MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
         {
         r_args[0] = 

#line 2846 "fsys.r"

            (&r_args[1])[n - 1];
         tend = r_tend.previous;
         return A_Continue;
         }
         }}
      }
   }

int Zwrites (int r_nargs, dptr r_args);
FncBlock(writes, -1, 0)

int Zwrites(r_nargs, r_args)
int r_nargs;
dptr r_args;
   {

#line 2868 "fsys.r"

   union f f;

#line 2872 "fsys.r"

   word status = 

#line 2881 "fsys.r"

   k_output.status;
   char r_sbuf[1][MaxCvtLen];
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[2];
      } r_tend;

   r_tend.d[1].dword = D_Null;
   r_tend.d[0].dword = F_Ptr | F_Nqual;
   r_tend.d[0].vword.bptr = (union block *)

#line 2870 "fsys.r"

      NULL;
   r_tend.num = 2;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;
   switch (

#line 2895 "fsys.r"

   (r_nargs - 0)) {
      case 0:{

#line 2668 "fsys.r"

         {

#line 2688 "fsys.r"

         (*(struct b_file**)&r_tend.d[0].vword.bptr) = &k_output;
         MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

         if ((k_output.status & Fs_Write) == 0) {
            MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
            {
            err_msg(

#line 2693 "fsys.r"

            213, NULL);
            tend = r_tend.previous;
            return A_Resume;
            }
            }
         else 

#line 2695 "fsys.r"

            {

            f.fp = k_output.fd.fp;
            }
         }

#line 2903 "fsys.r"

         {

#line 2787 "fsys.r"

         if (!(status & Fs_Messaging)) {

#line 2793 "fsys.r"

            if (!(status & Fs_Pty)) {

#line 2797 "fsys.r"

               if (!(status & Fs_Socket)) {

#line 2818 "fsys.r"

                  if (ferror(f.fp)) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 2820 "fsys.r"

                     214, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }

#line 2822 "fsys.r"

                  fflush(f.fp);
                  }
               }
            }

#line 2839 "fsys.r"

         MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
         {
         r_args[0] = 

#line 2846 "fsys.r"

            nulldesc;
         tend = r_tend.previous;
         return A_Continue;
         }
         }}
      default:

#line 2911 "fsys.r"

         {

#line 2920 "fsys.r"

         if (!(((&r_args[1])[0]).dword == D_File)) {

#line 2668 "fsys.r"

            

#line 2688 "fsys.r"

            (*(struct b_file**)&r_tend.d[0].vword.bptr) = &k_output;
            MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

            if ((k_output.status & Fs_Write) == 0) {
               MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               {
               err_msg(

#line 2693 "fsys.r"

               213, NULL);
               tend = r_tend.previous;
               return A_Resume;
               }
               }
            else 

#line 2695 "fsys.r"

               {

               f.fp = k_output.fd.fp;
               }
            }

#line 2923 "fsys.r"

         { 

         register word n;

#line 2930 "fsys.r"

         for (n = 0; n < (r_nargs - 0); n++) {
            if ((((&r_args[1])[n]).dword == D_File)) {

#line 3059 "fsys.r"

               status = BlkD((&r_args[1])[n], File)->status;
               if ((status & Fs_Write) == 0) {

                  if ((*(struct b_file**)&r_tend.d[0].vword.bptr)) 
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

                  {
                  err_msg(

#line 3065 "fsys.r"

                  213, &((&r_args[1])[n]));
                  tend = r_tend.previous;
                  return A_Resume;
                  }
                  }

#line 3067 "fsys.r"

               f.fp = BlkLoc((&r_args[1])[n])->File.fd.fp;

               (*(struct b_file**)&r_tend.d[0].vword.bptr) = BlkD((&r_args[1])[n], File);
               MUTEX_LOCKID_CONTROLLED((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
               }
            else 

#line 3081 "fsys.r"

               {

#line 3086 "fsys.r"

               if (!def_tstr(r_sbuf[0], &((&r_args[1])[n]), &(emptystr), &(r_tend.d[1]))) {
                  MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                  {
                  err_msg(

#line 3088 "fsys.r"

                  109, &((&r_args[1])[n]));
                  tend = r_tend.previous;
                  return A_Resume;
                  }
                  }

#line 3101 "fsys.r"

               if (status & Fs_Pty) 
                  ptputstr(f.pt, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1]));
               else 

#line 3118 "fsys.r"

               if (status & Fs_Messaging) {
                  struct MFile *mf = f.mf; 
                  extern int Merror;
                  Merror = 0;
                  tp_write(mf->tp, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1]));
                  if (Merror > 1200) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 3125 "fsys.r"

                     Merror, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               else 
               if (status & Fs_Socket) {

                  if (sock_write(f.fd, StrLoc(r_tend.d[1]), StrLen(r_tend.d[1])) < 0) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);

#line 3139 "fsys.r"

                     set_syserrortext(errno);
                     {
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               else 

#line 3143 "fsys.r"

                  {

                  if (putstr(f.fp, &r_tend.d[1]) == Failed) 
                     {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 3148 "fsys.r"

                     214, &((&r_args[1])[n]));
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }
                  }
               }
            }

#line 2787 "fsys.r"

         if (!(status & Fs_Messaging)) {

#line 2793 "fsys.r"

            if (!(status & Fs_Pty)) {

#line 2797 "fsys.r"

               if (!(status & Fs_Socket)) {

#line 2818 "fsys.r"

                  if (ferror(f.fp)) {
                     MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
                     {
                     err_msg(

#line 2820 "fsys.r"

                     214, NULL);
                     tend = r_tend.previous;
                     return A_Resume;
                     }
                     }

#line 2822 "fsys.r"

                  fflush(f.fp);
                  }
               }
            }

#line 2839 "fsys.r"

         MUTEX_UNLOCKID((*(struct b_file**)&r_tend.d[0].vword.bptr)->mutexid);
         {
         r_args[0] = 

#line 2846 "fsys.r"

            (&r_args[1])[n - 1];
         tend = r_tend.previous;
         return A_Continue;
         }
         }}
      }
   }

int Zgetch (dptr r_args);
FncBlock(getch, 0, 0)

int Zgetch(r_args)
dptr r_args;
   {

#line 3175 "fsys.r"

   {
   int i;

   i = getch();

#line 3184 "fsys.r"

   if (i < 0 || i > 255) 
      return A_Resume;
   {
   r_args[0].vword.sptr = 

#line 3186 "fsys.r"

      (char *)&allchars[FromAscii(i) & 0xFF];
   r_args[0].dword = 

#line 3186 "fsys.r"

      1;
   return A_Continue;
   }
   }
   }

int Zgetche (dptr r_args);
FncBlock(getche, 0, 0)

int Zgetche(r_args)
dptr r_args;
   {
   {
   int i;

   i = getche();

#line 3205 "fsys.r"

   if (i < 0 || i > 255) 
      return A_Resume;
   {
   r_args[0].vword.sptr = 

#line 3207 "fsys.r"

      (char *)&allchars[FromAscii(i) & 0xFF];
   r_args[0].dword = 

#line 3207 "fsys.r"

      1;
   return A_Continue;
   }
   }
   }

int Zkbhit (dptr r_args);
FncBlock(kbhit, 0, 0)

int Zkbhit(r_args)
dptr r_args;
   {

   {

   if (kbhit()) 
      {
      r_args[0] = 

#line 3221 "fsys.r"

         nulldesc;
      return A_Continue;
      }
   else 
      return A_Resume;
   }
   }

int Zchdir (dptr r_args);
FncBlock(chdir, 1, 0)

int Zchdir(r_args)
dptr r_args;
   {
   CURTSTATE_AND_CE();
   struct {
      struct tend_desc *previous;
      int num;
      struct descrip d[1];
      } r_tend;

   r_tend.d[0] = emptystr;
   r_tend.num = 1;
   r_tend.previous = tend;
   tend = (struct tend_desc *)&r_tend;

#line 3242 "fsys.r"

   if (!cnv_str(&(r_args[1]), &(r_args[1]))) {
      if (!((r_args[1]).dword == D_Null)) {
         {
         err_msg(

#line 3244 "fsys.r"

         103, &(r_args[1]));
         tend = r_tend.previous;
         return A_Resume;
         }
         }
      }

#line 3248 "fsys.r"

   {

#line 3264 "fsys.r"

   char path[PATH_MAX]; 
   int len;

   if ((!((r_args[1]).dword & F_Nqual))) {

      cnv_c_str(&(r_args[1]), &(r_tend.d[0]));

#line 3275 "fsys.r"

      if (strlen(r_tend.d[0].vword.sptr) > 2 && r_tend.d[0].vword.sptr[0] == '~' && r_tend.d[0].vword.sptr[1] == '/') {
         getenv_r("HOME", path, 1023);
         strcat(path, r_tend.d[0].vword.sptr + 1);
         r_tend.d[0].vword.sptr = path;
         }

      if (chdir(r_tend.d[0].vword.sptr) != 0) {
         set_syserrortext(errno);
         {
         tend = r_tend.previous;
         return A_Resume;
         }
         }
      }

   if (getcwd(path, 512) == NULL) {
      set_syserrortext(errno);
      {
      tend = r_tend.previous;
      return A_Resume;
      }
      }

#line 3295 "fsys.r"

   len = strlen(path);
   do {if ((StrLoc(r_args[0]) = alcstr(path, len)) == NULL) {
         err_msg(0, NULL);
         tend = r_tend.previous;
         return A_Resume;
         }
      }
   while (0);

#line 3297 "fsys.r"

   StrLen(r_args[0]) = len;
   {
   tend = r_tend.previous;
   return A_Continue;
   }
   }
   }

int Zdelay (dptr r_args);
FncBlock(delay, 1, 0)

int Zdelay(r_args)
dptr r_args;
   {
   C_integer r_i0;

#line 3335 "fsys.r"

   if (!cnv_c_int(&(r_args[1]), &(r_i0))) {
      {
      err_msg(

#line 3336 "fsys.r"

      101, &(r_args[1]));
      return A_Resume;
      }
      }

   {
   if (idelay(r_i0) == Failed) 
      return A_Resume;
   {
   r_args[0] = 

#line 3353 "fsys.r"

      nulldesc;
   return A_Continue;
   }
   }
   }

int Zflush (dptr r_args);
FncBlock(flush, 1, 0)

int Zflush(r_args)
dptr r_args;
   {

#line 3360 "fsys.r"

   if (!((r_args[1]).dword == D_File)) {
      {
      err_msg(

#line 3361 "fsys.r"

      105, &(r_args[1]));
      return A_Resume;
      }
      }

   {
   FILE *fp = BlkD(r_args[1], File)->fd.fp; 
   int status = BlkD(r_args[1], File)->status;

#line 3375 "fsys.r"

   if (((status & (Fs_Read | Fs_Write)) == 0) 

      || (status & Fs_Directory) 

#line 3380 "fsys.r"

      || (status & Fs_Socket)) 
      {
      r_args[0] = 
         r_args[1];
      return A_Continue;
      }

#line 3399 "fsys.r"

   fflush(fp);
   {
   r_args[0] = 

#line 3404 "fsys.r"

      r_args[1];
   return A_Continue;
   }
   }
   }

