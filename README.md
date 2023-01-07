jemu65c02
=========

This is a simple 65c02 emulator, written in C. It supports both 6502
instructions and 65c02 extended instructions. It provides a simple memory bus
callback mechanism for reads and writes, which allows user code to provide ROM,
RAM, and peripheral access. It provides a coarse grained run method that allows
the emulation to run for roughly a given number of cycles. This ensures that
external timing can be provided by the user to synchronize execution. This is
not as fine grained as is provided by game emulators (e.g. NES). This is meant
more for allowing for rapid prototyping of "roughly" equivalent circuits in
emulation on modern hardware before building a real 65c02 system.

This emulator also provides an interrupt and NMI triggering mechanism, so that
peripherals can be emulated using modern hardware. In theory, this emulator
could be programmed onto a modern ARM Cortex-M0+ device with a little glue
firmware to get a software emulated 6502 / 65c02 that works similarly to the
real thing. This emulation would not be timing or exact instruction sensitive,
but it would provide an upgrade path for miniaturizing 6502 based hardware and
boards.

Package
-------

This library uses C99 style inline functions and macros to provide packaging
support.

Packages are kept in a separate symbol namespace using the `JEMU_SYM` macro.
Each header roughly corresponds to a given package name. So, for instance, all
symbols for the the main header, `jemu65c02.h`, can be imported into a C source
file using the given macro:

```C
    #include <jemu65c02/jemu65c02.h>
    
    JEMU_IMPORT_jemu65c02;
    
    /* ... */
    
    j65c02* inst = NULL;
```

To prevent clashes with other libraries, a prefix import macro can be used
instead. In this case, the prefix must be prepended with an underscore to any
symbol names.

```C
    #include <jemu65c02/jemu65c02.h>
    
    JEMU_IMPORT_jemu65c02_as(mos);
    
    /* ... */
    
    mos_j65c02* inst = NULL;
```

In the library, symbol names are mangled in order to ensure that clashes are
unlikely. This mangling includes a UUID, the library version, and the symbol
name. Ultimately, this is what the `JEMU_SYM` macro means. This mangling ensures
that large projects which may depend on multiple libraries which may have
clashing symbol names normally can be linked safely. Obviously, there is a
trade-off between complete isolation and usability, but I've found that this
packaging concept works well in many large real-life projects.

Instance Lifetimes
------------------

This library follows a simplified resource-oriented style. Because it is so
simple, it does not take advantage of [RCPR][rcpr-link], but it does provide an
equivalent but simplified idiom. Instances are simplified resources. A
simplified resource always has one or more create methods, which act as the
equivalent of constructors in object-oriented languages. If this create method
returns a successful status code (i.e. a status code equal to zero), then the
caller owns the created instance and must release this instance when it is no
longer needed. In the [RCPR][rcpr-link] model, all instances are resources, and
the resource handles can be obtained so that they can be released. In the
simplified resource model in this library, there is always one release method
per instance type which can be used by the caller to release the instance when
it is no longer needed.

[rcpr-link]: https://github.com/nanolith/rcpr

For instance, the `j65c02` instance type has a single create method, named
`j65c02_create`. It also has a single release method, named `j65c02_release`. A
new processor emulator instance can be created by calling `j65c02_create`. When
this instance is no longer needed, it can be released by calling
`j65c02_release`.

j65c02 Interface
----------------

The `j65c02` interface consists of the following functions: create, step, run,
interrupt, nmi, and release. These functions allow for the complete exercise of
all 65c02 related functionality. However, these functions rely on two
user-provided callbacks, which are defined using the `j65c02_read_fn` and
`j65c02_write_fn` function types.

The `j65c02_status` value just provides a simple wrapper around an int return
code. This is used by all functions and callbacks. A zero return status is
considered a success, and a non-zero return status is considered a failure.

```C
    typedef int j65c02_status;
```

The `j65c02_read_fn` callback is provided with an opaque reference to a user
context (passed by the user in the constructor), a 16-bit address, and a pointer
to the 8-bit variable to be set with the value read at this address. If this
callback fails, it should return a non-zero status code. This status code will
end the current run and be bubbled up to the caller.

```C
    typedef j65c02_status (*j65c02_read_fn)(void*, uint16_t, uint8_t*);
```

The `j65c02_write_fn` callback is provided with an opaque reference to a user
context (passed by the user in the constructor), a 16-bit address, and an 8-bit
value to be written to this address. If this callback fails, it should return a
non-zero status code. This status code will end the current run and be bubbled
up to the caller.

```C
    typedef j65c02_status (*j65c02_write_fn)(void*, uint16_t, uint8_t);
```

To create a new emulator instance, the `j65c02_create` method is called. The
first argument is a pointer to the instance pointer, which receives the new
instance on success. The user is responsible for providing a read callback, a
write callback, and a user context value. This last value can be NULL if the
user does not need it. It will be passed to the read and write callback
functions, so it can be used by user code for house keeping, especially when
multiple emulators are being run or different boards are being emulated by user
code.

```C
    j65c02_status j65c02_create(
        j65c02** inst, j65c02_read_fn, j65c02_write_fn, void*);
```

The `j65c02_step` function runs a single instruction on the given emulator
instance. If the CPU is stopped or waiting for an interrupt, an appropriate
error message is returned.

```C
    j65c02_status j65c02_step(j65c02*, int);
```


The `j65c02_run` function runs the provided instance for up to the number of
cycles provided in the second argument. Because each instruction supported by
the 65(c)02 can take a different number of cycles to run, it's possible that
passing a number like 1000 cycles may end in the middle of an instruction. In
this case, to keep the emulation simple, this time is "added" to the instance
and the partial instruction is executed in full during the next time that the
run method is called. The run method only returns between instructions, which
simplifies interrupt and nmi logic. If the CPU is stopped or is waiting for an
interrupt, the run function will return successfully immediately, which makes
low-power emulation easier, as the emulator's CPU can get back to sleep faster.

```C
    j65c02_status j65c02_run(j65c02*, int);
```

The `j65c02_interrupt` function triggers the interrupt pin of the emulated
processor. During the next run, the interrupt functionality will be executed as
per the 65(c)02 manual, assuming that interrupts are enabled. If the
interrupt disable flag is set, then this function will end a CPU wait, but won't
trigger an interrupt.

```C
    j65c02_status j65c02_interrupt(j65c02*);
```

The `j65c02_nmi` function triggers the nmi pin of the emulated
processor. During the next run, the nmi handler will be executed as per
the 65(c)02 manual.

```C
    j65c02_status j65c02_nmi(j65c02*);
```

The `j65c02_release` function releases the provided `j65c02` instance. This
frees any memory associated with this instance and tears down any internal data
structures.

```C
    j65c02_status j65c02_release(j65c02*);
```

Error Handling
--------------

If the emulator encounters any errors, these will be returned to the caller.
User code should check the return values from all emulator functions. If an
error occurs after an emulator instance has been created, then the user must
still call `j65c02_release` to release this instance. If `j65c02_release` fails,
then this should be seen as a fatal error and execution should end after the
error is displayed to the end user.

Common reasons for errors would be the execution of an invalid instruction, a
processor error that would cause an error condition or reset in the 65(c)02, or
a user error from the read or write callbacks. This error handling mechanism can
be used to make the emulator much more pedantic than a real 65(c)02, which is
useful during unit testing or functional testing.

RAM, ROM, and Memory-Mapped I/O
-------------------------------

Since this emulator only concerns itself with emulating the 65(c)02, it is up to
the user to plug in ROM, RAM, or peripherals, using the read and write
callbacks. The callbacks can just map a 64k array that contains the program to
be executed, the zero page, and the one page. Or, it can check addresses to map
a 65(c)22 VIA, a UART, or any number of memory-mapped I/O peripherals. This is
up to the user. Future projects will provide some of these peripherals, which
can be easily plugged into this emulator.
