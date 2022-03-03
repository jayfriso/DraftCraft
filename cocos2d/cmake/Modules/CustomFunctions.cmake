function(copy_dll_post_step cocos_target dll_path dll_name )
    add_custom_command(TARGET ${cocos_target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${dll_path} "$<TARGET_FILE_DIR:${cocos_target}>/${dll_name}"
    )
endfunction()

function(copy_dll_post_step_for_folder cocos_target dll_folder_path)
    file(GLOB dll_paths ${dll_folder_path}*.dll)
    foreach(dll_path ${dll_paths})
        get_filename_component(dll_name ${dll_path} NAME)
        copy_dll_post_step(${cocos_target} ${dll_path} ${dll_name})
    endforeach()
endfunction()