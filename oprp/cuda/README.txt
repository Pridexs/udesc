Multiplicação de matrizes com CUDA.

O código foi feito para um caso peculiar

* Número de linhas deve ser igual ao número de colunas
* Número de linhas deve ser divisivel por 32

Testado com blocos de 32x32 Threads

Pode-se gerar um input para testar utilizando python3 generate_input.py <tamanho_matriz>

# Tempos:

| Método                        | Tempo 1024 | Tempo 2048 | Tempo 4096 | Tempo 6144 |
|-------------------------------|------------|------------|------------|------------|
| Serial                        | 8.61027    | 115.55706  | ---        | ---        |
| Cuda c/ Memória Global        | 0.02713    | 0.20379    | 1.83966    | 6.40315    |
| Cuda c/ Memória Compartilhada | 0.01364    | 0.09895    | 0.76345    | 2.54037    |

# Configurações da Placa de Vídeo Testada

```
Device 0: "GeForce GTX 960M"
  CUDA Driver Version / Runtime Version          8.0 / 8.0
  CUDA Capability Major/Minor version number:    5.0
  Total amount of global memory:                 2002 MBytes (2099642368 bytes)
  ( 5) Multiprocessors, (128) CUDA Cores/MP:     640 CUDA Cores
  GPU Max Clock rate:                            1176 MHz (1.18 GHz)
  Memory Clock rate:                             2505 Mhz
  Memory Bus Width:                              128-bit
  L2 Cache Size:                                 2097152 bytes
  Maximum Texture Dimension Size (x,y,z)         1D=(65536), 2D=(65536, 65536), 3D=(4096, 4096, 4096)
  Maximum Layered 1D Texture Size, (num) layers  1D=(16384), 2048 layers
  Maximum Layered 2D Texture Size, (num) layers  2D=(16384, 16384), 2048 layers
  Total amount of constant memory:               65536 bytes
  Total amount of shared memory per block:       49152 bytes
  Total number of registers available per block: 65536
  Warp size:                                     32
  Maximum number of threads per multiprocessor:  2048
  Maximum number of threads per block:           1024
  Max dimension size of a thread block (x,y,z): (1024, 1024, 64)
  Max dimension size of a grid size    (x,y,z): (2147483647, 65535, 65535)
  Maximum memory pitch:                          2147483647 bytes
  Texture alignment:                             512 bytes
  Concurrent copy and kernel execution:          Yes with 1 copy engine(s)
  Run time limit on kernels:                     Yes
  Integrated GPU sharing Host Memory:            No
  Support host page-locked memory mapping:       Yes
  Alignment requirement for Surfaces:            Yes
  Device has ECC support:                        Disabled
  Device supports Unified Addressing (UVA):      Yes
  Device PCI Domain ID / Bus ID / location ID:   0 / 1 / 0
```

# Código para gerar o gráfico

```{r}
cglobal <- c(0.02713, 0.20379, 1.83966, 6.40315)
cshared <- c(0.01364, 0.09895, 0.76345, 2.54037)
plot(cglobal, xaxt="n", type="o", col="red", xlab="Numero Linhas e Colunas", ylab="Tempo decorrido (segundos)")
lines(cshared, type="o", col="blue")
axis(1, at=1:4, labels=c("1024", "2048", "4096", "6144"))
legend("topleft",lty=1, col=c("red", "blue"), c("Cuda c/ Memoria Global","Cuda c/ Memoria Compartilhada"))
```
