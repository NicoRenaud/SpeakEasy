# ==== ====================================== ====
# ==== 	         SpeakEasy Makefile 	      ====
# ==== ====================================== ====
# Automatically generated the  20-11-2012 at 09h56


CC   = gcc

OBJ = OBJ/2d_spec_k1_12.o OBJ/2d_spec_k1_13.o OBJ/2d_spec_k1_13_v2.o OBJ/2d_spec_k1_23.o OBJ/2d_spec_k2_13.o OBJ/cplx_copy.o OBJ/cplx_diag.o OBJ/cplx_gen.o OBJ/cplx_inv.o OBJ/cplx_linalg.o OBJ/cplx_mvtrans.o OBJ/cplx_rotatebasis.o OBJ/copy.o OBJ/diag.o OBJ/gen.o OBJ/mvtrans.o OBJ/rotatebasis.o OBJ/define_matrices.o OBJ/define_total_matrices.o OBJ/disorder.o OBJ/convert.o OBJ/read_hamiltonian.o OBJ/read_input_file.o OBJ/main.o OBJ/export_gnuplot.o OBJ/export_scilab.o OBJ/print_screen.o 

LIBS = -lm  -lcblas -lclapack -lgsl
BIN  =  SPKZ
CFLAGS =  -Wall -pedantic -ansi
CFLAGS = 
RM = rm -f

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
		${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

OBJ/2d_spec_k1_12.o : ./SpeakEasy/2d_spec_k1/2d_spec_k1_12.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/2d_spec_k1/2d_spec_k1_12.c -o OBJ/2d_spec_k1_12.o

OBJ/2d_spec_k1_13.o : ./SpeakEasy/2d_spec_k1/2d_spec_k1_13.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/2d_spec_k1/2d_spec_k1_13.c -o OBJ/2d_spec_k1_13.o

OBJ/2d_spec_k1_13_v2.o : ./SpeakEasy/2d_spec_k1/2d_spec_k1_13_v2.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/2d_spec_k1/2d_spec_k1_13_v2.c -o OBJ/2d_spec_k1_13_v2.o

OBJ/2d_spec_k1_23.o : ./SpeakEasy/2d_spec_k1/2d_spec_k1_23.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/2d_spec_k1/2d_spec_k1_23.c -o OBJ/2d_spec_k1_23.o

OBJ/2d_spec_k2_13.o : ./SpeakEasy/2d_spec_k2/2d_spec_k2_13.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/2d_spec_k2/2d_spec_k2_13.c -o OBJ/2d_spec_k2_13.o

OBJ/cplx_copy.o : ./SpeakEasy/algebra_cplx/cplx_copy.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_cplx/cplx_copy.c -o OBJ/cplx_copy.o

OBJ/cplx_diag.o : ./SpeakEasy/algebra_cplx/cplx_diag.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_cplx/cplx_diag.c -o OBJ/cplx_diag.o

OBJ/cplx_gen.o : ./SpeakEasy/algebra_cplx/cplx_gen.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_cplx/cplx_gen.c -o OBJ/cplx_gen.o

OBJ/cplx_inv.o : ./SpeakEasy/algebra_cplx/cplx_inv.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_cplx/cplx_inv.c -o OBJ/cplx_inv.o

OBJ/cplx_linalg.o : ./SpeakEasy/algebra_cplx/cplx_linalg.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_cplx/cplx_linalg.c -o OBJ/cplx_linalg.o

OBJ/cplx_mvtrans.o : ./SpeakEasy/algebra_cplx/cplx_mvtrans.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_cplx/cplx_mvtrans.c -o OBJ/cplx_mvtrans.o

OBJ/cplx_rotatebasis.o : ./SpeakEasy/algebra_cplx/cplx_rotatebasis.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_cplx/cplx_rotatebasis.c -o OBJ/cplx_rotatebasis.o

OBJ/copy.o : ./SpeakEasy/algebra_real/copy.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_real/copy.c -o OBJ/copy.o

OBJ/diag.o : ./SpeakEasy/algebra_real/diag.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_real/diag.c -o OBJ/diag.o

OBJ/gen.o : ./SpeakEasy/algebra_real/gen.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_real/gen.c -o OBJ/gen.o

OBJ/mvtrans.o : ./SpeakEasy/algebra_real/mvtrans.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_real/mvtrans.c -o OBJ/mvtrans.o

OBJ/rotatebasis.o : ./SpeakEasy/algebra_real/rotatebasis.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/algebra_real/rotatebasis.c -o OBJ/rotatebasis.o

OBJ/define_matrices.o : ./SpeakEasy/create_system/define_matrices.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/create_system/define_matrices.c -o OBJ/define_matrices.o

OBJ/define_total_matrices.o : ./SpeakEasy/create_system/define_total_matrices.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/create_system/define_total_matrices.c -o OBJ/define_total_matrices.o

OBJ/disorder.o : ./SpeakEasy/disorder/disorder.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/disorder/disorder.c -o OBJ/disorder.o

OBJ/convert.o : ./SpeakEasy/input/convert.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/input/convert.c -o OBJ/convert.o

OBJ/read_hamiltonian.o : ./SpeakEasy/input/read_hamiltonian.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/input/read_hamiltonian.c -o OBJ/read_hamiltonian.o

OBJ/read_input_file.o : ./SpeakEasy/input/read_input_file.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/input/read_input_file.c -o OBJ/read_input_file.o

OBJ/main.o : ./SpeakEasy/main.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/main.c -o OBJ/main.o

OBJ/export_gnuplot.o : ./SpeakEasy/output/export_gnuplot.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/output/export_gnuplot.c -o OBJ/export_gnuplot.o

OBJ/export_scilab.o : ./SpeakEasy/output/export_scilab.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/output/export_scilab.c -o OBJ/export_scilab.o

OBJ/print_screen.o : ./SpeakEasy/output/print_screen.c
	$(CC) -c $(CFLAGS) ./SpeakEasy/output/print_screen.c -o OBJ/print_screen.o

