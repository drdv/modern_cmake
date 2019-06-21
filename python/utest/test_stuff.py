"""Utests for :obj:`stuff`."""
import os
import sys
import unittest

current_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(current_dir, '..'))
import stuff

class TestAlgebraicExpression(unittest.TestCase):
    """Perform utests for :obj:`stuff`. """

    def test_answer(self):
        """Test the answer."""
        self.assertEqual(stuff.answer(), 42)
