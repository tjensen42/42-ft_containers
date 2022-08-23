# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2022/08/22 11:48:55 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := tests

CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98#-O3#-g -fsanitize=address

CPPFLAGS    :=
DEPFLAGS     = -MT $@ -MMD -MP -MF $(DDIR)/$*.d

LDFLAGS     :=
LDLIBS      :=

VPATH       := ./ src/
SRCS        := tests.cpp vector_test.cpp stack_test.cpp map_test.cpp set_test.cpp

ODIR        := obj
OBJS        := $(SRCS:%.cpp=$(ODIR)/%.o)

DDIR        := $(ODIR)/.deps
DEPS        := $(SRCS:%.cpp=$(DDIR)/%.d)

# **************************************************************************** #
#   RULES                                                                      #
# **************************************************************************** #

.PHONY: all clean fclean re

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(ODIR)/%.o: %.cpp $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

$(DDIR):
	mkdir -p $@

all: $(NAME)

clean:
	$(RM) -r $(DDIR) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(DEPS):
include $(wildcard $(DEPS))
