PYTHON=python3
VENV_NAME=.venv

.PHONY: all
all:
	@echo "check available targets"

.PHONY: setup-venv
setup-venv:
	${PYTHON} -m venv ${VENV_NAME} && \
	. ${VENV_NAME}/bin/activate && \
	pip install --upgrade pip && \
	pip install -r .requirements.txt

.PHONY: clean-venv
clean-venv:
	rm -rf ${VENV_NAME}
