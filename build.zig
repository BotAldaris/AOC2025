// build.zig (Compatible with Zig 0.15.0 and later)

const std = @import("std");
const max_days = 2;

pub fn build(b: *std.Build) void {
    // In newer Zig, we grab the Allocator directly from the Build object.
    const allocator = b.allocator;

    // Target and Optimization options are still standard.
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Create a top-level step that depends on all day-part executables
    const all_day_parts = b.step("all-parts", "Builds all dayXX/partX executables.");
    const run_all_day_parts = b.step("run-all", "Runs all dayXX/partX executables.");

    for (2..max_days + 1) |day_num| {
        // --- Loop Setup ---
        // Format the day folder name (e.g., "day01")
        var day_dir_buf: [6]u8 = undefined; // "dayXX\0"
        const day_dir_name = std.fmt.bufPrintZ(&day_dir_buf, "day{0:0>2}", .{day_num}) catch @panic("Format error");

        // --- Part 1 Executable ---
        // Use the build allocator for transient strings.
        const part1_exe_name = std.fmt.allocPrint(allocator, "{s}-part1", .{day_dir_name}) catch @panic("Alloc error");
        const part1_path = std.fmt.allocPrint(allocator, "{s}/part1.zig", .{day_dir_name}) catch @panic("Alloc error");

        // 🎯 The Fix: Create a Module first, then pass it to addExecutable.
        const part1_module = b.createModule(.{
            .root_source_file = b.path(part1_path),
            .target = target,
            .optimize = optimize,
        });

        const part1_exe = b.addExecutable(.{
            .name = part1_exe_name,
            .root_module = part1_module, // Use the module here
        });

        // Add a build step for just this part (e.g., `zig build day01-part1`)
        const part1_step = b.step(part1_exe_name, std.fmt.allocPrint(allocator, "Builds Day {d} Part 1.", .{day_num}) catch @panic("Alloc error"));
        part1_step.dependOn(&part1_exe.step);
        all_day_parts.dependOn(part1_step);

        // Add a run step (e.g., `zig build run-day01-part1`)
        const run_part1 = b.addRunArtifact(part1_exe);
        const run_part1_step_name = std.fmt.allocPrint(allocator, "run-{s}", .{part1_exe_name}) catch @panic("Alloc error");
        const run_part1_step = b.step(run_part1_step_name, std.fmt.allocPrint(allocator, "Run Day {d} Part 1.", .{day_num}) catch @panic("Alloc error"));
        run_part1_step.dependOn(&run_part1.step);
        run_all_day_parts.dependOn(run_part1_step);

        // --- Part 2 Executable ---
        const part2_exe_name = std.fmt.allocPrint(allocator, "{s}-part2", .{day_dir_name}) catch @panic("Alloc error");
        const part2_path = std.fmt.allocPrint(allocator, "{s}/part2.zig", .{day_dir_name}) catch @panic("Alloc error");

        // 🎯 The Fix: Create a Module first, then pass it to addExecutable.
        const part2_module = b.createModule(.{
            .root_source_file = b.path(part2_path),
            .target = target,
            .optimize = optimize,
        });

        const part2_exe = b.addExecutable(.{
            .name = part2_exe_name,
            .root_module = part2_module, // Use the module here

        });

        // Add a build step for just this part (e.g., `zig build day01-part2`)
        const part2_step = b.step(part2_exe_name, std.fmt.allocPrint(allocator, "Builds Day {d} Part 2.", .{day_num}) catch @panic("Alloc error"));
        part2_step.dependOn(&part2_exe.step);
        all_day_parts.dependOn(part2_step);

        // Add a run step (e.g., `zig build run-day01-part2`)
        const run_part2 = b.addRunArtifact(part2_exe);
        const run_part2_step_name = std.fmt.allocPrint(allocator, "run-{s}", .{part2_exe_name}) catch @panic("Alloc error");
        const run_part2_step = b.step(run_part2_step_name, std.fmt.allocPrint(allocator, "Runs Day {d} Part 2.", .{day_num}) catch @panic("Alloc error"));
        run_part2_step.dependOn(&run_part2.step);
        run_all_day_parts.dependOn(run_part2_step);
    }

    // Add the top-level steps to the root "install" step
    const install_step = b.getInstallStep();
    install_step.dependOn(all_day_parts);
}
