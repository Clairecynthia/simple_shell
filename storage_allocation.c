#include "shell.h"

/**
 * _memset - Occupy a memory region with a specified byte value.
 * @dest: Pointer to the target memory area.
 * @byte: The byte value to fill the memory with.
 * @size: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area 'dest' after filling.
 */
	char *_memset(char *dest, char byte, unsigned int size)
	{
	unsigned int p;

	for (p = 0; p < size; p++)
	dest[p] = byte;
	return (dest);
}
/**
 * release_string_array - Releases memory used by an array of strings.
 * @str_array: Pointer to the array of strings to be released.
 */
	void release_string_array(char **str_array)
	{
	char **tmp = str_array;

	if (!str_array)
	return;

	while (*str_array)
	{
	free(*str_array);
	str_array++;
	}

	free(tmp);
	}

/**
 * custom_realloc - Reassigns a block of memory.
 * @ptr: Pointer to the previously assigned memory block.
 * @old_size: The size in bytes of the previous memory block.
 * @new_size: The desired size in bytes for the new memory block.
 *
 * Return: Pointer to the newly allocated memory block, or NULL on failure.
 */
	void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
	{
	char *new_ptr;

	if (!ptr)
	return (malloc(new_size));

	if (!new_size)
	{
	free(ptr);
	return (NULL);
	}

	if (new_size == old_size)
	return (ptr);

	new_ptr = malloc(new_size);

	if (!new_ptr)
	return (NULL);

	unsigned int copy_size = (old_size < new_size) ? old_size : new_size;
	for (unsigned int i = 0; i < copy_size; i++)

	new_ptr[i] = ((char *)ptr)[i];

	free(ptr);
	return (new_ptr);
	}

/**
 * free_and_null - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free and nullify.
 *
 * Return: 1 if freed and set to NULL, otherwise 0.
 */
	int free_and_null(void **ptr)
	{
	if (ptr && *ptr)
	{
	free(*ptr);
	*ptr = NULL;
	return (1);
	}
	return (0);
	}
