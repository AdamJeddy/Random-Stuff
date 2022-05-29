#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <math.h>

#define ARRAY_SIZE 1000

char* getOpenCLProgramFromFile(const char* filename) {
    FILE* programFile;
    char* programSource;
    size_t program_source_size;

    programFile = fopen(filename, "rb");
    if (!programFile) 
    {
        printf("Failed to load kernel \n");
        exit(1);
    }

    // Get file length and allocate space to read the contents
    fseek(programFile, 0, SEEK_END);
    program_source_size = ftell(programFile);
    programSource = (char*)malloc(program_source_size + 1);

    // Rewind the file to the beginning, read the contents, and add a null terminator
    rewind(programFile);
    fread(programSource, sizeof(char), program_source_size, programFile);
    programSource[program_source_size] = '\0';

    fclose(programFile);
    return programSource;
}


void callStatus(char* task, int err) {
    printf("%s: [%s] (%d)\n", task, err == 0 ? "OK" : "FAILED", err);
}

int main()
{
    cl_int       	err;
    cl_platform_id   platform;
    cl_device_id 	device;

    cl_context   	context;
    cl_command_queue commandQueue;
    cl_program   	program;
    cl_kernel    	kernel;

    cl_mem       	buffer;

    err = clGetPlatformIDs(1, &platform, NULL);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

    // create a context
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    callStatus("Creating a Context", err);

    // create a queue
    commandQueue = clCreateCommandQueue(context, device, NULL, &err);
    callStatus("Creating a Command Queue", err);

    // Get program from file
    const char* initArrayKernel = getOpenCLProgramFromFile("kernelFile.txt");

    // create program from source
    program = clCreateProgramWithSource(context, 1, &initArrayKernel, NULL, &err);
    callStatus("Creating Program from Source", err);

    // build the program
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    callStatus("Building Program", err);

    // fetch a kernel
    kernel = clCreateKernel(program, "initializeArray", &err);
    callStatus("Creating Kernel from Program", err);

    // create device memory for the array
    buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * ARRAY_SIZE, NULL, &err);
    callStatus("Creating Buffer", err);

    // set kernel's arguments
    unsigned int count = ARRAY_SIZE;
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);
    callStatus("Setting Parameter 0 (__global int* input)", err);
    err = clSetKernelArg(kernel, 1, sizeof(unsigned int), &count);
    callStatus("Setting Parameter 1 (const unsigned int count)", err);

    size_t local = 10;
    size_t global = ceil(count / (float)local) * local;

    // enqueue kernel runs kernel with all work items
    err = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
    callStatus("Started the Work", err);

    //* Blocks until all previously queued OpenCL commands finished
    err = clFinish(commandQueue);
    callStatus("Waiting for the Work to Finish", err);

    // read output from device memory to host memory
    int results[ARRAY_SIZE];
    clEnqueueReadBuffer(commandQueue, buffer, CL_TRUE, 0, sizeof(int) * ARRAY_SIZE, results, 0, NULL, NULL);

    // check correctness of kernel by printing the contents of the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", results[i]);
    }

    // release OpenCL objects
    clReleaseMemObject(buffer);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commandQueue);
    clReleaseContext(context);

    free((void *)initArrayKernel);
    system("PAUSE");
    return 0;
}
