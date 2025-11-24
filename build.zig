const std = @import("std");
const builtin = @import("builtin");

pub fn build(b: *std.Build) !void {
    const t = b.standardTargetOptions(.{});
    const o = b.standardOptimizeOption(.{});

    buildCoreLibrary(b, t, o);

    const exe = b.addExecutable(.{
        .name = "Game",
        .target = t,
        .optimize = o,
    });

    var name: []const u8 = undefined;
    if (builtin.os.tag  == .macos) {
        name = "main.c";
    } else {
        name = "main.c";
    }

    exe.linkLibC();
    exe.addCSourceFiles(.{
        .root = b.path("src/"),
        .files = &[_][]const u8{
            name,
        },
        .flags = &[_][]const u8{
            "-std=c99",
            "-Wall",
        },
    });

    linkFrameworks(exe);
    installHeaders(b, exe);


    exe.addIncludePath(b.path("src/"));
    exe.addIncludePath(b.path("src/shaders"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}

pub fn buildCoreLibrary(
    b: *std.Build,
    t: std.Build.ResolvedTarget,
    o: std.builtin.OptimizeMode,
) void {

    const exe = b.addSharedLibrary(.{
        .name = "Core",
        .target = t,
        .optimize = o,
    });


    exe.linkLibC();
    exe.addCSourceFiles(.{
        .root = b.path("src/core"),
        .files = &[_][]const u8{
            "c_main.c",
        },
        .flags = &[_][]const u8{
            "-std=c99",
            "-Wall",
        },
    });

    b.installArtifact(exe);
}

pub fn linkFrameworks(
    exe: *std.Build.Step.Compile,
) void {
    switch (builtin.os.tag) {
        .macos => {
            exe.linkFramework("Cocoa");
            exe.linkFramework("Metal");
            exe.linkFramework("MetalKit");
            exe.linkFramework("IOKit");
        },
        else => {},
    }
}

pub fn installHeaders(
    b: *std.Build,
    exe: *std.Build.Step.Compile,
) void {
    exe.addIncludePath(b.path("src/thirdparty/"));
    exe.installHeader(b.path("src/thirdparty/stb_image.h"), "stb_image.h");
    exe.installHeader(b.path("src/thirdparty/sokol_app.h"), "sokol_app.h");
    exe.installHeader(b.path("src/thirdparty/sokol_audio.h"), "sokol_audio.h");
    exe.installHeader(b.path("src/thirdparty/sokol_gfx.h"), "sokol_gfx.h");
    exe.installHeader(b.path("src/thirdparty/sokol_log.h"), "sokol_log.h");
    exe.installHeader(b.path("src/thirdparty/sokol_glue.h"), "sokol_glue.h");
}
