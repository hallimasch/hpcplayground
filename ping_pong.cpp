#include <iostream>
#include <mpi.h>

int main(int argc, char** argv)
{
	const int PING_PONG_LIMIT = 10;

	MPI_Init(&argc, &argv);
	
	// find out the rank and size
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	// assuming with 2 processs
	if (world_size != 2)
	{
		std::cout << "World size must be two for " << argv[0] << std::endl;
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	
	int ping_pong_count = 0;
	int partner_rank = 1 - my_rank;
	while (ping_pong_count < PING_PONG_LIMIT)
	{
		++ping_pong_count;
		if (my_rank == (ping_pong_count+1)%2)
		{
			MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
			std::cout << my_rank << " sent and incremented ping_pong_count " << ping_pong_count << " to " << partner_rank << std::endl; 
		}
		else
		{
			MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::cout << my_rank << " received ping_pong_count " << ping_pong_count << " from " << partner_rank << std::endl;
		}
	}

	MPI_Finalize();

	return 0;
}
