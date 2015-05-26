/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zion <zion@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:45 by zion              #+#    #+#             */
/*   Updated: 2015/05/20 21:58:52 by zion             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

// #ifdef __APPLE__
// # define __gl_h_
// # define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
// #endif

# include <libft.h>
// # define GLFW_INCLUDE_GLU
// # define GL_GLEXT_PROTOTYPES
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

GLuint LoadShaders(const char *vertex_file_path,const char *fragment_file_path);

#endif
